/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:40:35 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/12 20:15:22 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Pauses the program execution to 
**	receive the user's input and writes
**	it to an fd while it's open
*/
static void	here_doc(char *delim, int *fd)
{
	char	*line;
	int		written[2];

	set_signals(HEREDOC);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(delim, line, ft_strlen(delim) + 1))
		{
			free(line);
			break ;
		}
		written[0] = write(fd[1], line, ft_strlen(line));
		written[1] = write(fd[1], "\n", 1);
		free(line);
		if (written[0] < 0 || written[1] < 0)
		{
			perror("heredoc fd");
			break ;
		}
	}
	close(fd[0]);
	close(fd[1]);
	exit_program(0);
}

static int	fork_heredoc(char *delim, int *fd)
{
	int		wstatus;
	pid_t	forked;

	if (!delim || !*delim || pipe(fd) < 0)
		return (-1);
	get_control()->status = 0;
	set_signals(INACTIVE);
	forked = fork();
	if (!forked)
		here_doc(delim, fd);
	if (forked < 0)
		perror("fork");
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

static int	validate_hdoc(int fd)
{
	if (fd < 0)
	{
		perror("fd");
		return (0);
	}
	if (get_control()->status == 130)
		return (0);
	return (1);
}

int	get_heredoc(t_token *tok, t_cli *cli)
{
	if (!tok || !cli)
		return (0);
	while (cli)
	{
		while (tok && tok->type != HEREDOC && tok->type != PIPE)
			tok = tok->next;
		if (!tok || tok->type == PIPE)
			cli = cli->next;
		else if (tok->type == HEREDOC && tok->next)
		{
			if (cli->hdoc > 0)
				close(cli->hdoc);
			cli->hdoc = fork_heredoc(tok->next->str, cli->fd);
			cli->fd[0] = 0;
			cli->fd[1] = 0;
			if (!validate_hdoc(cli->hdoc))
				return (0);
		}
		if (tok)
			tok = tok->next;
	}
	return (1);
}
