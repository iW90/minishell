/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:22:50 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/05 13:59:55 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_cli *commands)
{
	int	i;

	i = 0;
	while (commands)
	{
		i++;
		commands = commands->next;
	}
	return (i);
}

static void	fork_command(t_cli *commands)
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
		get_control()->status = 127;
	}
	exit_program(0);
}

static void	wait_last_command(pid_t forked, int *wstatus)
{
	waitpid(forked, wstatus, 0);
	if (WIFEXITED(*wstatus))
		get_control()->status = (WEXITSTATUS(*wstatus));
	set_signals(ACTIVE);
}

static int	mother_forker(t_cli *commands)
{
	pid_t	*forks;
	int		fork_amount;
	int		wstatus;

	wstatus = 0;
	fork_amount = count_commands(commands);
	set_signals(INACTIVE);
	while (commands)
	{
		forked = fork();
		if (!forked)
			fork_command(commands);
		if (forked < 0)
			return (-1);
		else
		{
			if (commands->fd[0] > 0)
				close(commands->fd[0]);
			if (commands->fd[1] > 0)
				close(commands->fd[1]);
			if (!commands->next)
				wait_last_command(forked, &wstatus);
		}
		commands = commands->next;
	}
	return (wstatus);
}

int	run_commands(void)
{
	t_cli	*commands;

	commands = get_control()->commands;
	if (!commands)
		return (0);
	if (commands->next || commands->fd[0] || commands->fd[1])
		return (mother_forker(commands));
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
		get_control()->status = 127;
	}
	return (1);
}