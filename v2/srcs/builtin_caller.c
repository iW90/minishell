/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_caller.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:34:20 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/22 19:07:58 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_builtin(t_cli *cli)
{
	t_ctrl	*ctrl;
	char	*builtin;
	char	**args;

	if (!cli)
		return ;
	builtin = cli->args[0];
	args = cli->args[1];
	ctrl = get_control();
	if (!ft_strcmp(builtin, "cd"))
		ctrl->status = b_cd(args);
	else if (!ft_strcmp(builtin, "pwd"))
		ctrl->status = b_pwd();
	else if (!ft_strcmp(builtin, "echo"))
		ctrl->status = b_echo(args);
	else if (!ft_strcmp(builtin, "unset"))
		ctrl->status = b_unset(args, ctrl->env);
	else if (!ft_strcmp(builtin, "export"))
		ctrl->status = b_export(ctrl->env, args);
	else if (!ft_strcmp(builtin, "env"))
		ctrl->status = b_env(args, ctrl->env);
	else if (!ft_strcmp(builtin, "exit"))
		b_exit(args);
}
