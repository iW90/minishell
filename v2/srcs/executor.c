/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:22:50 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/05 22:43:24 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_command(t_cli *commands, pid_t *forked)
{
	if (commands->fd[0] > 0)
	{
		if (dup2(commands->fd[0], STDIN_FILENO) < 0)
			exit_program(-1);
		close(commands->fd[0]);
	}
	if (commands->fd[1])
	{
		if (dup2(commands->fd[1], STDOUT_FILENO) < 0)
			exit_program(-1);
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

void	execute_a_command(t_cli *commands)
{
	if (commands->type == BUILTIN)
		call_builtin(commands);
	else if (commands->type == EXEC)
		call_execve(commands->args, get_control()->env);
	else
	{
		ft_putstr_fd("Command ", STDERR_FILENO);
		if (commands->args)
			ft_putstr_fd(commands->args[0], STDERR_FILENO);
		ft_putstr_fd(" not found\n", STDERR_FILENO);
		if (get_control()->status == 126)	
			return ;
		get_control()->status = 127;
	}
}
