/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:07:00 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/07 21:40:25 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_str_digit(char *arg)
{
	int	i;

	i = -1;
	if (arg[i + 1] == '-' || arg[i + 1] == '+')
		i++;
	while (arg[++i])
		if (!ft_isdigit(arg[i]))
			return (0);
	return (1);
}

int	b_exit(char **args)
{
	if (!args || !*args)
		return (exit_program(0), 0);
	if (is_str_digit(args[0]) && !args[1])
		exit_program(ft_atoi(args[0]) % 256);
	if (is_str_digit(args[0]) && args[1])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	if (!is_str_digit(args[0]))
	{
		ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
		exit_program(2);
	}
	return (exit_program(0), 0);
}
