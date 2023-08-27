/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:29:53 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/27 11:55:07 by maalexan         ###   ########.fr       */
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
	printf("before going to the loop:\n");
	print_token(tok);
	print_cli();
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
			cli = cli->next;
	}
	print_cli();
}

/*
Below are only test files
*/


static char	*print_type(int type)
{
	if (type == PIPE)
		return ("pipe");
	else if (type == HEREDOC)
		return ("heredoc");
	else if (type == APPEND)
		return ("append");
	else if (type == INPUT)
		return ("input");
	else if (type == OVERWRITE)
		return ("overwrite");
	else if (type == BUILTIN)
		return ("builtin");
	else if (type == EXEC)
		return ("exec");
	else if (type == ARGUMENT)
		return ("arg");
	else
		return ("");
}

void	print_token(t_token *tokens)
{
	static int	count;

	if (!tokens)
	{
		printf("no tokens here\n");
		count = 0;
		return ;
	}
	printf("I'm at token %i str: %s | type: %s\n", count++, tokens->str, print_type(tokens->type));
	print_token(tokens->next);
}

static void	print_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
	{
		printf("No args\n");
		return ;
	}
	while(*args)
		printf("arg[%i] %s / ", i++, *args++);
	printf("EOA\n");
}

void print_cli(void)
{
	t_cli	*current;
	int		i;

	i = 1;
	current = get_control()->commands;
	while (current)
	{
		printf("\nCli number %i\n", i++);
		if (current->args)
			print_args(current->args);
		printf("fd0 is %i and fd1 is %i\n", current->fd[0], current->fd[1]);
		printf("type %s\n", print_type(current->type));
		current = current->next;
	}
}