/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:07:41 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/14 21:36:54 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	run_fork(char **args, t_env *env)
{
	char	**packed_env;

	packed_env = stringify_env(env);
	set_signals(DEFAULT);
	if (execve(args[0], args, packed_env) < 0)
	{
		ft_putstr_fd("Failed to run program ", STDERR_FILENO);
		ft_putstr_fd(args[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		clear_ptr_array(packed_env);
		exit_program(126);
	}
}

void	call_execve(char **args, t_env *env)
{
	pid_t	forked;
	int		wstatus;

	wstatus = 0;
	set_signals(INACTIVE);
	forked = fork();
	if (!forked)
		run_fork(args, env);
	if (forked < 0)
		ft_putstr_fd("Failed to create child process\n", STDERR_FILENO);
	else
	{
		waitpid(forked, &wstatus, 0);
		if (WIFEXITED(wstatus))
			get_control()->status = (WEXITSTATUS(wstatus));
	}
}
