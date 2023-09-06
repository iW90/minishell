/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 19:58:43 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/05 21:22:42 by maalexan         ###   ########.fr       */
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

static int	count_commands(t_cli *commands)
{
	int	i;

	i = 0;
	while (commands)
	{
		commands = commands->next;
		i++;
	}
	return (i);
}

int	run_commands(void)
{
	t_cli	*commands;
	pid_t	*forks;
	int		amount;

	commands = get_control()->commands;
	if (!commands)
		return (0);
	if (commands->next || commands->fd[0] || commands->fd[1])
	{
		amount = count_commands(commands);
		forks = malloc(sizeof(pid_t) * amount);
		if (!forks)
			exit_program(OUT_OF_MEMORY);
		set_signals(INACTIVE);
		mother_forker(commands, forks, amount);
		set_signals(ACTIVE);
		free(forks);
	}
	else
		execute_a_command(commands);
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