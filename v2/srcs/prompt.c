/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:58:43 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/02 21:04:13 by maalexan         ###   ########.fr       */
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
	if (commands->fd[0] > 0)
	{
		if (dup2(commands->fd[0], STDIN_FILENO) < 0)
			exit_program(-1);
		close(commands->fd[0]);
	}
	if (commands->fd[1])
	{
		if (dup2(commands->fd[1], STDOUT_FILENO) < 0)
			exit_program(-1);
		close(commands->fd[1]);
	}
	if (commands->type == BUILTIN)
		call_builtin(commands);
	else if (commands->type == EXEC)
		call_execve(commands->args, get_control()->env);
	else
	{
		ft_putstr_fd("Command ", STDERR_FILENO);
		if (commands->args)
			ft_putstr_fd(commands->args[0], STDERR_FILENO);
		ft_putstr_fd(" not found\n", STDERR_FILENO);
		get_control()->status = 127;
	}
	exit_program(0);
}

static int	mother_forker(t_cli *commands)
{
	pid_t	forked;
	int		wstatus;
	int		last_command;

	wstatus = 0;
	last_command = 0;
	while (commands)
	{
		forked = fork();
		if (!forked)
			fork_command(commands);
		if (forked < 0)
			return (-1);
		else
		{
			if (commands->fd[0] > 0)
				close(commands->fd[0]);
			if (commands->fd[1] > 0)
				close(commands->fd[1]);
			if (!commands->next)
				last_command = 1;
		}
		commands = commands->next;
	}
	waitpid(forked, &wstatus, 0);
	if (WIFEXITED(wstatus) && last_command)
		get_control()->status = (WEXITSTATUS(wstatus));
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
	else
	{
		ft_putstr_fd("Command ", STDERR_FILENO);
		if (commands->args)
			ft_putstr_fd(commands->args[0], STDERR_FILENO);
		ft_putstr_fd(" not found\n", STDERR_FILENO);
		get_control()->status = 127;
	}
	return (1);
}

void	prompt_user(const char *prompt)
{
	t_ctrl	*control;

	control = get_control();
	set_signals(ACTIVE);
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

/*


t_token *discard_tokens(t_token *tok)
{
	t_token	*start;

	start = tok;
	while (start && start->prev && start->prev->type != PIPE)
		start = start->prev;

}


t_token *discard_tokens(t_token *tok)
{
    if (!tok)
        return NULL;

    t_token *current = tok;
    t_token *prev_boundary = NULL;
    t_token *next_boundary = NULL;

    while (current->prev && current->prev->type != PIPE)
        current = current->prev;
    prev_boundary = current->prev;
    current = tok;
    while (current->next && current->next->type != PIPE)
        current = current->next;
    next_boundary = current->next;
    if (next_boundary && next_boundary->type == PIPE)
    {
        t_token *tmp = next_boundary->next;
        remove_token(next_boundary);
        next_boundary = tmp;
    }
    current = tok;
    while (current != next_boundary)
    {
        t_token *tmp = current->next;
        remove_token(current);
        current = tmp;
    }
    if (prev_boundary)
        prev_boundary->next = next_boundary;
    if (next_boundary)
        next_boundary->prev = prev_boundary;
    return next_boundary;
}


static int	assign_each_fd(t_cli *cli, t_token *tok, t_here *heredocs)
{
	while (tok)
	{
		if (tok->type <= PIPE)
		{
			tok = tok->prev;
			if (tok->next->type == PIPE)
			{
				cli = pipe_fd(cli->next);
				tok = tok->next->next;
				if (heredocs && heredocs->next)
					heredocs = heredocs->next;
			}
			else
				get_fd(tok->next, cli->fd, heredocs);
			if (cli && (cli->fd[0] < 0 || cli->fd[1] < 0))
			{
				cli = remove_bad_node(cli);
				tok = discard_tokens(tok->next);
				if (!tok)
					break ;
			}
			if (get_control()->status == 130)
				return (0);
		}
		tok = tok->next;
	}
	return (1);
}

*/