/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:40:35 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/02 14:50:22 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Pauses the program execution to 
**	receive the user's input and writes
**	it to an fd while it's open
*/
static void	here_doc(char *delim, char *line, int *fd)
{
	int		written[2];

	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(delim, line, ft_strlen(delim) + 1))
			break ;
		written[0] = write(fd[1], line, ft_strlen(line));
		written[1] = write(fd[1], "\n", 1);
		free(line);
		if (written[0] < 0 || written[1] < 0)
			break ;
	}
	exit_program(0);
}

static void	prepare_here_doc(char *delim, int *fd, t_here *head)
{
	t_cli	*cli;

	free_heredocs(head, 0);
	cli = malloc(sizeof(t_cli));
	if (!cli)
		exit_program(OUT_OF_MEMORY);
	*cli = (t_cli){0};
	cli->args = malloc(sizeof(char *) * 2);
	if (!cli->args)
		exit_program(OUT_OF_MEMORY);
	cli->args[0] = NULL;
	cli->args[1] = NULL;
	cli->fd[0] = fd[0];
	cli->fd[1] = fd[1];
	get_control()->commands = cli;
	set_signals(HEREDOC);
	here_doc(delim, cli->args[0], cli->fd);
}

static int	fork_heredoc(char *delim, t_here *head)
{
	int		fd[2];
	int		wstatus;
	pid_t	forked;

	if (!delim || !*delim || pipe(fd) < 0)
		return (-1);
	get_control()->status = 0;
	set_signals(INACTIVE);
	forked = fork();
	if (!forked)
		prepare_here_doc(delim, fd, head);
	if (forked < 0)
		ft_putstr_fd("Failed to create child process\n", STDERR_FILENO);
	else
	{
		waitpid(forked, &wstatus, 0);
		if (WIFEXITED(wstatus))
			get_control()->status = (WEXITSTATUS(wstatus));
	}
	close(fd[1]);
	set_signals(ACTIVE);
	return (fd[0]);
}

t_here	*get_heredocs(t_token *tok)
{
	t_here	*start;
	t_here	*cursor;

	if (!has_heredoc(tok))
		return (NULL);
	start = make_new_heredoc(NULL);
	cursor = start;
	while (tok)
	{
		if (tok->type == HEREDOC && tok->next)
		{
			if (cursor->fd)
				close(cursor->fd);
			cursor->fd = fork_heredoc(tok->next->str, start);
			if (get_control()->status == 130)
				return (start);
		}
		else if (tok->type == PIPE && has_heredoc(tok))
		{
			cursor->next = make_new_heredoc(start);
			cursor = cursor->next;
		}
		tok = tok->next;
	}
	return (start);
}
