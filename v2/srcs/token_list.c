/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:49:59 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/08 15:10:12 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	link_token(t_token *current, t_token *last)
{
	if (!current || !last)
		return ;
	while (last->next)
		last = last->next;
	last->next = current;
	current->prev = last;
}

t_token	*remove_token(t_token *node)
{
	t_token	*prev;
	t_token	*next;

	if (!node)
		return (NULL);
	prev = node->prev;
	next = node->next;
	if (node->str)
		free(node->str);
	free(node);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (!prev && !next)
		get_control()->tokens = NULL;
	return (next);
}

static t_token	*get_token_end(t_token *token)
{
	t_token	*end;

	end = token;
	while (end && end->type != PIPE)
		end = end->next;
	if (end)
		end = end->next;
	return (end);
}

static t_token	*get_token_stt(t_token *token)
{
	t_token	*stt;

	stt = token;
	while (stt && stt->prev && stt->prev->type != PIPE)
		stt = stt->prev;
	return (stt);
}

t_token	*discard_tokens(t_token *token)
{
	t_token	*stt;
	t_token	*end;

	if (!token)
		return (NULL);
	end = get_token_end(token);
	stt = get_token_stt(token);
	token = stt;
	if (!stt->prev)
		get_control()->tokens = end;
	stt = stt->prev;
	while (token != end)
		token = remove_token(token);
	if (end)
		end->prev = stt;
	if (stt)
	{
		if (!stt->next)
			remove_token(stt);
		else
			stt->next = end;
	}
	return (end);
}
