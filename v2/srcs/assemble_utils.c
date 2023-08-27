/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:49:48 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/26 19:09:00 by maalexan         ###   ########.fr       */
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

void	free_heredocs(t_here *doc)
{
	if (!doc)
		return ;
	free_heredocs(doc->next);
	free(doc);
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

t_cli	*make_new_cli(t_here *head)
{
	t_cli	*node;

	node = malloc(sizeof(t_cli));
	if (!node)
	{
		free_heredocs(head);
		exit_program(OUT_OF_MEMORY);
	}
	*node = (t_cli){0};
	return (node);
}
