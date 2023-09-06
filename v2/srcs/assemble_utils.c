/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:49:48 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/05 21:29:10 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *node)
{
	int	count;

	count = 0;
	while (node && node->type == ARGUMENT)
	{
		node = node->next;
		count++;
	}
	return (count);
}

int	count_nodes(t_token *tok)
{
	int	count;

	count = 0;
	while (tok)
	{
		if (tok->type > PIPE)
		{
			count++;
			while (tok && tok->type != PIPE)
				tok = tok->next;
		}
		else if (tok->type == PIPE)
		{
			count++;
			tok = tok->next;
		}
	}
	return (count);
}

int	has_heredoc(t_token	*tok)
{
	while (tok)
	{
		if (tok->type == HEREDOC)
			return (1);
		tok = tok->next;
	}
	return (0);
}

void	free_heredocs(t_here *doc, char closing)
{
	if (!doc)
		return ;
	free_heredocs(doc->next, closing);
	if (closing)
		close(doc->fd);
	free(doc);
}

t_cli	*pipe_fd(t_cli *cli)
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