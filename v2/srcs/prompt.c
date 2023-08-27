/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:58:43 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/27 15:42:14 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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

void	run_commands(void)
{
	t_cli	*commands;

	commands = get_control()->commands;
	while (commands)
	{
		if (commands->type == EXEC)
			call_execve(commands->args, get_control()->env);
		commands = commands->next;
	}
}

void	prompt_user(const char *prompt)
{
	t_ctrl	*control;

	control = get_control();
	set_signals(DEFAULT);
	control->status = 0;
	control->input = readline(prompt);
	if (!control->input)
		exit_program(0);
	add_history(control->input);
	if (!validate_input(control->input))
	{
		tokenization(control->input);
		parser();
//		print_tokens(control->tokens);
		assemble_tokens(control->tokens);
		run_commands();
		control->tokens = NULL;
	}
	free(control->input);
}
