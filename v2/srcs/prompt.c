/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:58:43 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/15 08:10:26 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *tokens)
{
	if (!tokens)
		return ;
	printf("str: %s\n", tokens->str);
	if (tokens->type == PIPE)
		printf("pipe\n");
	else if (tokens->type == HEREDOC)
		printf("heredoc\n");
	else if (tokens->type == APPEND)
		printf("append\n");
	else if (tokens->type == INPUT)
		printf("input\n");
	else if (tokens->type == OVERWRITE)
		printf("overwrite\n");
	else if (tokens->type == BUILTIN)
		printf("builtin\n");
	else if (tokens->type == EXEC)
		printf("exec\n");
	else if (tokens->type == ARGUMENT)
		printf("arg\n");
	print_tokens(tokens->next);
}

void	prompt_user(const char *prompt, t_env *env_list)
{
	t_ctrl	*control;

	control = get_control();
	set_signals(ACTIVE);
	control->status = 0;
	(void)env_list;
//	control->path = get_var_value("PATH", env_list);
	control->input = readline(prompt);
	if (!control->input)
		exit_program(0);
	add_history(control->input);
	if (!validate_input(control->input))
	{
		//printf("Teste\n");
		tokenization(control->input);
		print_tokens(control->tokens);
	}
	free(control->input);
	control->input = NULL;
}
