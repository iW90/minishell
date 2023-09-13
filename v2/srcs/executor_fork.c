/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:33:55 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/12 21:47:16 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_command(t_cli *commands, pid_t *forked)
{
	if (commands->fd[0] > 0)
	{
		if (dup2(commands->fd[0], STDIN_FILENO) < 0)
		{
			free(forked);
			exit_program(1);
		}
		close(commands->fd[0]);
	}
	if (commands->fd[1])
	{
		if (dup2(commands->fd[1], STDOUT_FILENO) < 0)
		{
			free(forked);
			exit_program(1);
		}
		close(commands->fd[1]);
	}
	free(forked);
	execute_a_command(commands);
	exit_program(0);
}

static void	wait_commands(pid_t *forked, int amount)
{
	int	i;
	int	wstatus;

	i = 0;
	while (i < amount)
	{
		waitpid(forked[i], &wstatus, 0);
		if (WIFEXITED(wstatus) && i == (amount - 1))
			get_control()->status = WEXITSTATUS(wstatus);
		i++;
	}
}

int	mother_forker(t_cli *commands, pid_t *forked, int amount)
{
	int		i;

	i = 0;
	while (commands)
	{
		forked[i] = fork();
		if (!forked[i])
			fork_command(commands, forked);
		if (forked[i] < 0)
			return (-1);
		else
		{
			if (commands->fd[0] > 0)
				close(commands->fd[0]);
			if (commands->fd[1] > 0)
				close(commands->fd[1]);
		}
		commands = commands->next;
		i++;
	}
	wait_commands(forked, amount);
	return (i);
}
