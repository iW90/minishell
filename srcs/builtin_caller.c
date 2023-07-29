/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_caller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:34:20 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/28 21:08:47 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(char *builtin, char **args, t_env *env)
{
	t_ctrl	*ctrl;

	if (!builtin)
		return ;
	ctrl = get_control();
	if (!ft_strncmp(builtin, "ping", 5))
		ctrl->last_exit = printf("pong\n");
	else if (!ft_strncmp(builtin, "cd", 3))
		ctrl->last_exit = b_cd(args, env);
	else if (!ft_strncmp(builtin, "pwd", 4))
		ctrl->last_exit = b_pwd();
	else if (!ft_strncmp(builtin, "echo", 5))
		ctrl->last_exit = b_echo(args);
	else if (!ft_strncmp(builtin, "unset", 6))
		ctrl->last_exit = b_unset(env, args);
	else if (!ft_strncmp(builtin, "export", 7))
		ctrl->last_exit = b_export(env, args);
	else if (!ft_strncmp(builtin, "env", 4))
		ctrl->last_exit = b_env(args, env);
	else if (!ft_strncmp(builtin, "exit", 5))
		b_exit(args);
}
