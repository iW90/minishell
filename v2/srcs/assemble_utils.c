/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:49:48 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/24 17:36:54 by maalexan         ###   ########.fr       */
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

void	remove_token(t_token *node)
{
	t_token	*prev;
	t_token	*next;

	if (!node)
		return ;
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

 /*
token tok1						token tok2					token tok3						token tok4						token tok5
{								{							{								{								{
	tok1->str = "cat";				tok2->str = "file";			tok3->str = ">>";				tok4->str = "outputted";		tok5->str = "|";
	tok1->type = EXEC;				tok2->type = ARG;			tok3->type = APPEND;			tok4->type = ARG;				tok5->type = PIPE;
	tok1->prev = NULL;				tok2->prev = tok1;			tok3->prev = tok2;				tok4->prev = tok3;				tok5->prev = tok4;
	tok1->next = tok2;				tok2->next = tok3;			tok3->next = tok4;				tok4->next = tok5;				tok5->next = tok6;
}								}							}								}								}


token tok6						token tok7					token tok8						token tok9					
{								{							{								{							
	tok6->str = "grep";				tok7->str = "example";		tok8->str = "<";				tok9->str = "f.txt";	
	tok6->type = EXEC;				tok7->type = ARG;			tok8->type = INPUT;				tok9->type = ARG;		
	tok6->prev = tok5;				tok7->prev = tok6;			tok8->prev = tok7;				tok9->prev = tok8;		
	tok6->next = tok7;				tok2->next = tok8;			tok8->next = tok9;				tok9->next = NULL;		
}								}							}								}			
*/