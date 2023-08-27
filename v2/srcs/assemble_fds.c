/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:27:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/27 11:05:02 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cli	*pipe_fd(t_token *tok, t_cli *cli)
{
	if (!cli)
		return (NULL);
	cli->type = PIPE;
	if (pipe(cli->fd) < 0)
	{
		cli->fd[0] = -1;
		cli->fd[1] = -1;
	}
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

static void get_fd(t_token *tok, int *fd, t_here *heredocs)
{
	int		redirector;

	redirector = tok->type;
	if (fd[0] > 0 && (redirector == INPUT || redirector == HEREDOC))
	{
		close(fd[0]);
		fd[0] = 0;
	}
	if (fd[1] > 0 && (redirector == APPEND || redirector == OVERWRITE))
	{
		close(fd[1]);
		fd[1] = 0;
	}
	if (prepare_fd(tok, fd, heredocs) < 0)
	{
		if ((redirector == INPUT || redirector == HEREDOC))
			fd[0] = -1;
		if ((redirector == APPEND || redirector == OVERWRITE))
			fd[1] = -1;
	}
}

static int	assign_each_fd(t_cli *cli, t_token *tok, t_here *heredocs)
{
	while (tok)
	{
		if (tok->type <= PIPE)
		{
			tok = tok->prev;
			if (tok->next->type == PIPE)
			{
				cli = pipe_fd(tok->next, cli->next);
				if (heredocs->next)
					heredocs = heredocs->next;
			}
			else
				get_fd(tok->next, cli->fd, heredocs);
			if (get_control()->status == 130)
				return (0) ;
		}
		tok = tok->next;
	}
	return (1);
}

void	assemble_fds(t_cli *cli, t_token *tok, t_here *heredocs)
{
	int		nodes;
	int		assigned;

	nodes = count_nodes(tok);
	while (--nodes)
	{
		cli->next = make_new_cli(heredocs);
		cli = cli->next;
	}
	cli = get_control()->commands;
	assigned = assign_each_fd(cli, tok, heredocs);
	free_heredocs(heredocs, 0);
	if (assigned)
		printf("done\n");
	print_token(get_control()->tokens);
}
