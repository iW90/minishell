/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:27:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/24 20:40:48 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cli	*pipe_fd(t_token *tok, t_cli *cli)
{
	if (!cli)
		return (NULL);
	cli->type = PIPE;
	if (pipe(cli->fd) < 0)
		cli->fd[0] = -1;
	remove_token(tok);
	return (cli->next);
}

/*
**	Makes sure the t_cli node has it's input and
**	output file descriptor properly set
*/
static int	prepare_fd(t_token *node, int *fd, t_here *heredocs)
{
	t_token	*next;
	char	*file;
	int		redirector;

	if (!node || !node->next || !node->next->str)
		return (-1);
	next = node->next;
	file = next->str;
	redirector = node->type;
	if (redirector == HEREDOC)
		fd[0] = heredocs->fd;
	else if (redirector == INPUT)
		fd[0] = open(file, O_RDONLY);
	else if (redirector == APPEND)
		fd[1] = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (redirector == OVERWRITE)
		fd[1] = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	remove_token(next);
	remove_token(node);
	if (fd[0] == -1 && (redirector == HEREDOC || redirector == INPUT))
		return (-1);
	if (fd[1] == -1 && (redirector == APPEND || redirector == OVERWRITE))
		return (-1);
	return (0);
}

static t_here	*get_fd(t_token *tok, int *fd, t_here *heredocs)
{
	int		type;
	t_here	*start;

	start = heredocs;
	type = tok->type;
	if (fd[0] > 0 && (type == INPUT || type == HEREDOC))
	{
		close(fd[0]);
		fd[0] = 0;
		if (prepare_fd(tok, fd, heredocs) < 0)
			fd[0] = -1;
	}
	if (fd[1] > 0 && (type == APPEND || type == OVERWRITE))
	{
		close(fd[1]);
		fd[1] = 0;
		if (prepare_fd(tok, fd, heredocs) < 0)
			fd[1] = -1;
	}
	if (type == HEREDOC)
	{
		heredocs = heredocs->next;
		free(start);
	}
	return (heredocs);
}

void	assemble_fds(t_cli *cli, t_token *tok, t_here *heredocs)
{
	int	nodes;

	nodes = count_nodes(tok);
	while (--nodes)
	{
		cli->next = make_new_cli(heredocs);
		cli = cli->next;
	}
	cli = get_control()->commands;
	while (tok)
	{
		if (tok->type > PIPE)
			tok = tok->next;
		else
		{
			tok = tok->prev;
			if (tok->type == PIPE)
				cli = pipe_fd(tok->next, cli->next);
			else
				heredocs = get_fd(tok->next, cli->fd, heredocs);
		}
		tok = tok->next;
		cli = cli->next;
	}
}
