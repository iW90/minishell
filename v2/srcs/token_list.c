/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:49:59 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/16 22:50:58 by inwagner         ###   ########.fr       */
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
