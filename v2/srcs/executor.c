/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 09:31:26 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/08 09:31:39 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
