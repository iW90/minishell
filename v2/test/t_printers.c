/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_printers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:16:35 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/10 23:12:54 by maalexan         ###   ########.fr       */
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

void	print_tokens(t_token *tokens)
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
		if (current->hdoc)
			printf("heredoc is fd %i\n", current->hdoc);
		printf("type %s\n", print_type(current->type));
		current = current->next;
	}
}

/*
static char	*print_type(t_token *tokens)
{
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
	printf("str: %s | type: %s\n", tokens->str, print_type(tokens));
	print_tokens(tokens->next);
}
*/
