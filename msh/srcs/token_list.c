/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:49:59 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/14 19:58:48 by inwagner         ###   ########.fr       */
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
