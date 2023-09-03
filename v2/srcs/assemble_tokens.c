/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 13:29:53 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/03 10:05:52 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*print_type_tok(t_token *tokens)
{
	if (!tokens)
		return ("");
	if (tokens->type == PIPE)
		return ("pipe");
	else if (tokens->type == HEREDOC)
		return ("heredoc");
	else if (tokens->type == APPEND)
		return ("append");
	else if (tokens->type == INPUT)
		return ("input");
	else if (tokens->type == OVERWRITE)
		return ("overwrite");
	else if (tokens->type == BUILTIN)
		return ("builtin");
	else if (tokens->type == EXEC)
		return ("exec");
	else if (tokens->type == ARGUMENT)
		return ("arg");
	else
		return ("");
}

static void	print_tokens(t_token *tokens)
{
	if (!tokens)
		return ;
	printf("str: %s | type: %s\n", tokens->str, print_type_tok(tokens));
	print_tokens(tokens->next);
}

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
	printf("NULL\n");
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

static t_cli	*change_fds(t_cli *before, t_cli *piped, t_cli *after)
{
	if (!before || !piped || !after)
		return (NULL);
	if (before->fd[1] > 2 || after->fd[0] > 2)
	{
		close(piped->fd[0]);
		close(piped->fd[1]);
	}
	else
	{
		before->fd[1] = piped->fd[1];
		after->fd[0] = piped->fd[0];
	}
	free(piped);
	before->next = after;
	return (after);
}

static int	pipe_chain(t_cli *cli)
{
	t_cli	*piped;
	t_cli	*after;

	piped = NULL;
	after = NULL;
	while (cli)
	{
		if (cli->next && cli->next->type == PIPE)
		{
			piped = cli->next;
			if (piped->next && piped->next->type != PIPE)
				after = piped->next;
		}
		if (!piped && !after)
			return (1);
		cli = change_fds(cli, piped, after);
		piped = NULL;
		after = NULL;
	}
	return (0);
}

static int	set_command_chain(t_cli *cli, t_token *tok)
{
	if (get_control()->commands == cli)
		print_cli();
	if (get_control()->tokens == tok)
		print_tokens(tok);
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
	pipe_chain(get_control()->commands);
	return (1);
}

int	assemble_tokens(t_token *tok)
{
	t_cli	*cli;
	t_here	*heredocs;

	if (!tok)
		return (0);
	heredocs = get_heredocs(tok);
	if (get_control()->status == 130)
	{
		free_heredocs(heredocs, 'c');
		return (0);
	}
	cli = make_new_cli(heredocs);
	get_control()->commands = cli;
	if (!assemble_fds(cli, tok, heredocs))
		return (0);
	return (set_command_chain(get_control()->commands, tok));
}
