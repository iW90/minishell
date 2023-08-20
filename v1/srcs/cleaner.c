/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:25:37 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/18 20:48:52 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	clear_var_list(t_env *list)
{
	if (!list)
		return ;
	clear_var_list(list->next);
	if (list->key)
		free(list->key);
	free(list);
}

void	clear_command_input(t_cli *cli)
{
	if (!cli)
		return ;
	clear_command_input(cli->next);
	if (cli->cmd)
		free(cli->cmd);
	if (cli->args)
		clear_ptr_array(cli->args);
	if (cli->director)
		free(cli->director);
	if (cli->exec)
		free(cli->exec);
	free(cli);
}

void	clear_ptr_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

t_ctrl	*get_control(void)
{
	static t_ctrl	control;

	return (&control);
}

void	exit_program(int code)
{
	t_ctrl	*control;

	control = get_control();
	if (control->env)
		clear_var_list(control->env);
	if (control->cli)
		clear_command_input(control->cli);
	rl_clear_history();
	if (control->read_line)
		free(control->read_line);
	if (code)
		exit((unsigned char)code);
	exit((unsigned char)control->last_exit);
}
