/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/30 13:59:01 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	command_count(void)
{
	static unsigned int	count;

	return (count++);
}

static void	apply_prompt(char *line, char *path)
{
	t_cli	*cmds;
	t_ctrl	*ctrl;
	char	*expanded;

	ctrl = get_control();
	expanded = expand_line(line);
	free(line);
	ctrl->read_line = expanded;
	cmds = parse_input(expanded, path);
	if (cmds)
	{
		update_env(cmds->args, cmds->cmd, cmds->exec);
		call_builtin(cmds->cmd, cmds->args, ctrl->env);
		call_execve(cmds->exec, cmds->args, ctrl->env);
	}
	if (ctrl->cli)
		clear_command_input(cmds);
	ctrl->cli = NULL;
	if (expanded)
		free(expanded);
	ctrl->read_line = NULL;
}

void	prompt_user(const char *prompt, t_env *env_list)
{
	char	*line;
	char	*path;

	set_signals(ACTIVE);
	path = get_var_value("PATH", env_list);
	line = readline(prompt);
	if (!command_count() && !line)
		exit_program(127);
	else if (!line)
		exit_program(0);
	add_history(line);
	if (!bar_input(line))
		apply_prompt(line, path);
	else
		free(line);
}

int	main(int argc, char **argv, char **env)
{
	t_ctrl	*control;

	(void)argc;
	control = get_control();
	control->env = parse_env(env);
	update_env(argv, NULL, NULL);
	while (1)
		prompt_user("minishell:> ", control->env);
	exit_program(0);
}
