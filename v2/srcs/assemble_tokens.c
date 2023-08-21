/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:29:53 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/21 19:00:35 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Builds the arguments for a node that
**	starts with an argument, a builtin or exec
**	getting rid of the t_tokens as it goes
*/

char	**assemble_command_node(t_token *node)
{
	int		i;
	int		count;
	char	**args;
	t_token	*temp;

	i = 0;
	if (node->type == BUILTIN || node->type == EXEC)
		count = count_args(node->next) + 2;
	else
		count = count_args(node) + 1;
	args = malloc(sizeof(char *) * count);
	if (!args)
		exit_program(OUT_OF_MEMORY);
	while (i < count)
	{
		args[i++] = node->str;
		node->str = NULL;
		temp = node->next;
		remove_token(node);
		node = temp;
	}
	args[i] = NULL;
	return (args);
}

t_cli	*make_new_node(t_token *tok)
{
	t_cli	*node;

	if (!tok)
		return (NULL);
	node = malloc(sizeof(t_cli));
	if (!node)
		exit_program(OUT_OF_MEMORY);
	*node = (t_cli){0};
	return (node);
}

t_token	*get_last_fd(t_cli *node, t_token *current)
{
	t_token	*prev;

	prev = current->prev;
	while (current && current->type > PIPE)
	{
		if (node->fd[0] && (current->type == INPUT || current->type == HEREDOC))
		{
			close(node->fd[0]);
			node->fd[0] = 0;
		}
		if (node->fd[1] && (current->type == APPEND || current->type == OVERWRITE))
		{
			close(node->fd[1]);
			node->fd[1] = 0;
		}
		if (prepare_fd(current, node->fd) < 0)
			exit_program(FD_ERROR);
		current = prev->next;
	}
	return (prev);
}

void	assemble_tokens(t_token *tok_nav)
{
	t_cli	*cli_nav;

	if (!tok_nav)
		return ;
	cli_nav = make_new_node(tok_nav);
	get_control()->commands = cli_nav;
	while (1)
	{
		cli_nav->type = tok_nav->type;
		if (tok_nav->type > PIPE)
			cli_nav->args = assemble_command_node(tok_nav);
		else if (tok_nav->type < PIPE)
			tok_nav = get_last_fd(cli_nav, tok_nav);
		else if (pipe(cli_nav->fd) < 0)
			exit_program(FD_ERROR);
		tok_nav = tok_nav->next;
		if (tok_nav)
			cli_nav->next = make_new_node(tok_nav);
		else
			break ;
		cli_nav = cli_nav->next;
	}
}


/*
Model tokens

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



fd[0] fd[1]


cli1								cli2								cli3									
{									{									{										
	cli1->args[0] = "cat";				cli->args = NULL;					cli->args[0] = "grep";				
	cli1->args[1] = "file";				cli->type = PIPE;					cli->args[1] = "example";
	cli1->args[2] = NULL;				cli->fd[0] = pipedRead;				cli->type = EXEC;
	cli1->type = EXEC;					cli->fd[1] = pipedWrite;			cli->fd[0] = copyFromCli2;//overwritten by tok8-9
	cli1->fd[0] = 0;					cli->next = cli3;					cli->fd[1] = 0;
	cli1->fd[1] = duped(tok3-4);											cli->next = NULL;
	cli->next = cli2;
}									}									}


*/