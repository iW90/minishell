/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:58:43 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/27 22:45:01 by maalexan         ###   ########.fr       */
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

static void	fork_command(t_cli *commands)
{
	if (commands->fd[0])
		if (dup2(commands->fd[0], STDIN_FILENO) < 0)
			exit_program(-1);
	if (commands->fd[1])
		if (dup2(commands->fd[1], STDOUT_FILENO) < 0)
			exit_program(-1);
	if (commands->type == BUILTIN)
		call_builtin(commands);
	else if (commands->type == EXEC)
		call_execve(commands->args, get_control()->env);
	exit_program(0);
}

static int	mother_forker(t_cli *commands)
{
	pid_t	forked;
	int		wstatus;

	wstatus = 0;
	while (commands)
	{
		forked = fork();
		if (!forked)
			fork_command(commands);
		if (forked < 0)
		{
			ft_putstr_fd("Failed to create child process\n", STDERR_FILENO);
			break ;
		}
		else
		{
			waitpid(forked, &wstatus, 0);
			if (WIFEXITED(wstatus))
				get_control()->status = (WEXITSTATUS(wstatus));
		}
		commands = commands->next;
	}
	return (wstatus);
}

int	run_commands(void)
{
	t_cli	*commands;

	commands = get_control()->commands;
	if (!commands)
		return (0);
	if (commands->next || commands->fd[0] || commands->fd[1])
		return (mother_forker(commands));
	if (commands->type == BUILTIN)
		call_builtin(commands);
	else if (commands->type == EXEC)
		call_execve(commands->args, get_control()->env);
	return (1);
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
		if (assemble_tokens(control->tokens))
			run_commands();
		control->tokens = NULL;
		clear_cli(control->commands);
		control->commands = NULL;
	}
	free(control->input);
}
