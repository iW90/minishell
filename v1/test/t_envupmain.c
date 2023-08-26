/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/03 20:03:33 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	better_env(t_env *list)
{
	t_env	*cursor;

	if (!list)
		return ;
	cursor = list->next;
	while (cursor)
	{
		printf("%s=%s\n", cursor->key, cursor->value);
		cursor = cursor->next;
	}
	printf("%s=%s\n", list->key, list->value);
}

void	prompt_user(const char *prompt, t_env *env_list)
{
	char	*line;
	t_cli	*cmds;
	t_ctrl	*ctrl;
	char	*path;
	char	**argv;

	argv = NULL;
	path = get_var_value("PATH", env_list);
	line = readline(prompt);
	if (!line)
		exit_program(127);
	cmds = parse_input(line, path);
	ctrl = get_control();
	if (ctrl->cli)
	{
		if (ctrl->cli->args)
			argv = stringify_args(ctrl->cli->args);
		update_env(argv, ctrl->cli->cmd);
		if (argv)
		{
			clear_ptr_array(argv);
			argv = NULL;
		}
		better_env(ctrl->env);
		clear_command_input(cmds);
	}
	ctrl->cli = NULL;
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	t_ctrl	*control;

	(void)argc;
	control = get_control();
	control->env = parse_env(env);
	update_env(argv, NULL);
	better_env(control->env);
	while (1)
		prompt_user("minishell:> ", control->env);
}
