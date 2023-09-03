/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_fds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:27:33 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/03 10:58:51 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cli	*pipe_fd(t_cli *cli)
{
	if (!cli)
		return (NULL);
	cli->type = PIPE;
	if (pipe(cli->fd) < 0)
	{
		cli->fd[0] = -1;
		cli->fd[1] = -1;
	}
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

	if (!node || !node->next || !node->next->str)
		return (-1);
	next = node->next;
	file = next->str;
	if (node->type == HEREDOC)
		fd[0] = heredocs->fd;
	else if (node->type == INPUT)
		fd[0] = open(file, O_RDONLY);
	else if (node->type == APPEND)
		fd[1] = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (node->type == OVERWRITE)
		fd[1] = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	if (fd[0] == -1 || fd[1] == -1)
		perror(file);
	remove_token(next);
	remove_token(node);
	if (fd[0] == -1 || fd[1] == -1)
		return (-1);
	return (0);
}

static void	get_fd(t_token *tok, int *fd, t_here *heredocs)
{
	int		redirector;

	redirector = tok->type;
	if (fd[0] > 0 && (redirector == INPUT))
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
				cli = pipe_fd(cli->next);
				tok = tok->next->next;
				if (heredocs && heredocs->next)
					heredocs = heredocs->next;
			}
			else
				get_fd(tok->next, cli->fd, heredocs);
			if (cli && (cli->fd[0] < 0 || cli->fd[1] < 0))
			{
				printf("gonna print the clis: \n");
				print_cli();
				if (cli->next)
					remove_cli(cli->next);
				cli = remove_cli(cli);
				printf("just removed the first and maybe the second cli, now I'm left with:\n");
				print_cli();
				printf("ok so the tokens are here:\n");
				print_token(tok);
				printf("done printing tokens\n");
				tok = discard_tokens(tok);
				printf("after the removing token part:\n");
				print_token(tok);
				printf("gonna print the structure now:\n");
				print_token(get_control()->tokens);
				if (!tok)
					break ;
			}
			if (get_control()->status == 130)
				return (0);
		}
		tok = tok->next;
	}
	return (1);
}

int	assemble_fds(t_cli *cli, t_token *tok, t_here *heredocs)
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
	return (assigned);
}
