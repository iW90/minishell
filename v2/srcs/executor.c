/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:31:26 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/13 10:00:11 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_a_command(t_cli *commands)
{
	if (!commands)
		return ;
	if (commands->fd[0] < 0 || commands->fd[1] < 0)
	{
		get_control()->status = 1;
		return ;
	}
	if (commands->type == BUILTIN)
		call_builtin(commands);
	else if (commands->type == EXEC)
		call_execve(commands->args, get_control()->env);
	else
	{
		ft_putstr_fd(" command not found\n", STDERR_FILENO);
		if (get_control()->status == 126)
			return ;
		get_control()->status = 127;
	}
}

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
	if (commands->next || commands->fd[0] > 0 || commands->fd[1] > 0)
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
