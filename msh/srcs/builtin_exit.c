/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:07:00 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/16 13:30:58 by inwagner         ###   ########.fr       */
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

static int	print_error_exit(char *str, int ex)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (ex)
		exit_program(ex);
	return (1);
}

int	b_exit(char **args)
{
	int	is_number;

	if (!args || !*args)
		return (exit_program(0), 0);
	is_number = is_str_digit(args[0]);
	if (is_number && !args[1])
		exit_program(ft_atoi(args[0]) % 256);
	if (is_number && args[1])
		return (print_error_exit("exit: too many arguments\n", 0));
	if (!is_number)
		print_error_exit("exit: numeric argument required\n", 2);
	return (exit_program(0), 0);
}
