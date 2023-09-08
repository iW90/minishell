/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:49:48 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/08 10:30:59 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
