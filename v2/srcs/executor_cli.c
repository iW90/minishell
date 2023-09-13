/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cli.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:33:33 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/13 11:43:28 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token *node)
{
	int	count;

	count = 0;
	while (node && node->type != PIPE)
	{
		node = node->next;
		count++;
	}
	return (count);
}

static char	**get_cli(t_token *token)
{
	int		i;
	int		count;
	char	**args;
	t_token	*temp;

	i = 0;
	count = count_args(token) + 1;
	args = malloc(sizeof(char *) * count);
	if (!args)
		exit_program(OUT_OF_MEMORY);
	while (i < count - 1)
	{
		args[i++] = token->str;
		token->str = NULL;
		temp = token->next;
		remove_token(token);
		token = temp;
	}
	get_control()->tokens = token;
	args[i] = NULL;
	return (args);
}

int	set_cli(t_token *tok, t_cli *cli)
{
	while (cli && tok)
	{
		if (tok->type > PIPE)
		{
			cli->type = tok->type;
			cli->args = get_cli(tok);
		}
		tok = get_control()->tokens;
		if (!tok)
			break ;
		if (tok->type == PIPE)
		{
			tok = tok->next;
			if (tok && tok->prev)
				remove_token(tok->prev);
			else
				remove_token(tok);
			cli = cli->next;
		}
	}
	return (1);
}
