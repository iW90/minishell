/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/11 20:54:42 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args)
{
	int			i;

	i = 1;
	while (*args)
		printf("\nPRINTING ARGS\narg%i: %s\n", i++, *args++);
}

static void	print_cmds(void)
{
	t_ctrl	*ctrl = get_control();
	t_cli	*temp;

	if (ctrl)
		temp = ctrl->cli;
	else
		temp = NULL;
	int	i = 1;
	while (temp)
	{
		if (temp && temp->cmd)
			printf("Command %i: %s\n", i, temp->cmd);
		if (temp && temp->args)
			print_args(temp->args);
		if (temp && temp->director)
			printf("Dir %i: %s\n", i, temp->director);
		if (temp && temp->exec)
			printf("Exec: %i: %s\n", i, temp->exec);
		i++;
		temp = temp->next;
		write(1, "\n", 1);
	}
}

void	prompt_user(const char *prompt, t_env *env_list)
{
	char	*line;
	t_cli	*cmds;
	t_ctrl	*ctrl;
	char	*path;
	char	*exp;

	exp = NULL;
	path = get_var_value("PATH", env_list);
	line = readline(prompt);
	if (!line)
		exit_program(127);
	exp = expand_line(line);
	printf ("Test:\n%s\n", exp);
	cmds = parse_input(line, path);
	ctrl = get_control();
	if (ctrl->cli)
	{
		print_cmds();
		clear_command_input(cmds);
	}
	ctrl->cli = NULL;
	if (exp)
		free(exp);
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	t_ctrl	*control;

	(void)argc;
	control = get_control();
	control->env = parse_env(env);
	update_env(argv, NULL);
	while (1)
		prompt_user("minishell:> ", control->env);
}
