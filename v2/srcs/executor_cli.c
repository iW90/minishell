/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cli.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:33:33 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/08 11:33:35 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cli(t_token *tok)
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

void	create_cli_list(t_token *tok, t_here *heredocs)
{
	int		cli_len;
	t_cli	*cli;

	cli = add_cli(heredocs);
	get_control()->commands = cli;
	cli_len = count_cli(tok);
	while (--cli_len)
	{
		cli->next = add_cli(heredocs);
		cli = cli->next;
	}
}

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

int	set_cli(t_cli *cli, t_token *tok)
{
	while (cli && tok)
	{
		cli->type = tok->type;
		if (tok->type > PIPE)
			cli->args = get_cli(tok);
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
	return (1);
}
