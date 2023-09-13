/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_constructor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:33:40 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/13 09:57:33 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	build_cli(int count)
{
	t_cli	*cli;

	if (!count)
		return (0);
	cli = malloc(sizeof(t_cli));
	if (!cli)
		return (-1);
	*cli = (t_cli){0};
	get_control()->commands = cli;
	while (--count)
	{
		cli->next = malloc(sizeof(t_cli));
		cli = cli->next;
		if (!cli)
			return (-1);
		*cli = (t_cli){0};
	}
	return (1);
}

static int	count_cli(t_token *tok)
{
	int	count;

	if (!tok)
		return (0);
	count = 1;
	while (tok)
	{
		if (tok->type == PIPE)
			count++;
		tok = tok->next;
	}
	return (count);
}

static void	pipe_fd(int *next_fd0, int *curr_fd1, int *piped_fd)
{
	if (*next_fd0 == 0)
		*next_fd0 = piped_fd[0];
	else
		close(piped_fd[0]);
	*curr_fd1 = piped_fd[1];
}

static int	set_pipes(t_cli *cli)
{
	int		fd[2];
	t_cli	*next;

	next = cli->next;
	while (next)
	{
		fd[0] = 0;
		fd[1] = 0;
		if (!cli->fd[1])
		{
			if (pipe(fd) < 0)
			{
				perror("pipe");
				return (-1);
			}
			else
			pipe_fd(&next->fd[0], &cli->fd[1], fd);
		}
		cli = next;
		next = next->next;
	}
	return (1);
}

int	executor_constructor(t_token *tok)
{
	int		count;
	t_ctrl	*ctrl;

	if (!tok)
		return (0);
	ctrl = get_control();
	count = count_cli(tok);
	if (build_cli(count) < 0)
		exit_program(OUT_OF_MEMORY);
	if (!get_heredoc(tok, ctrl->commands))
		return (0);
	set_fd(ctrl->tokens, ctrl->commands);
	set_cli(ctrl->tokens, ctrl->commands);
	if (!ctrl->commands || set_pipes(ctrl->commands) < 0)
		return (0);
	return (1);
}
