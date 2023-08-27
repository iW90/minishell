/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:29:53 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/27 15:25:40 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Builds the arguments for a node that
**	starts with an argument, a builtin or exec
**	getting rid of the t_tokens as it goes
*/
static char	**assemble_command_node(t_token *node)
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
	while (i < count - 1)
	{
		args[i++] = node->str;
		node->str = NULL;
		temp = node->next;
		remove_token(node);
		node = temp;
	}
	get_control()->tokens = node;
	args[i] = NULL;
	return (args);
}

void	assemble_tokens(t_token *tok)
{
	t_cli	*cli;
	t_here	*heredocs;

	if (!tok)
		return ;
	heredocs = get_heredocs(tok);
	if (get_control()->status == 130)
	{
		free_heredocs(heredocs, 'c');
		return ;
	}
	cli = make_new_cli(heredocs);
	get_control()->commands = cli;
	assemble_fds(cli, tok, heredocs);
	while (1)
	{
		cli->type = tok->type;
		if (tok->type > PIPE)
			cli->args = assemble_command_node(tok);
		tok = get_control()->tokens;
		if (!tok)
			break ;
		cli = cli->next;
		if (cli->type == PIPE)
		{
			tok = tok->next;
			remove_token(tok->prev);
			cli = cli->next;
		}
	}
}
