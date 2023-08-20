/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 20:57:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/17 19:33:10 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(char **args)
{
	while (*args)
	{
		ft_putstr_fd(*args++, STDOUT_FILENO);
		if (*args)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
}

int	b_echo(char **args)
{
	if (!args)
		return (0);
	if (ft_strncmp(*args, "-n\0", 3))
	{
		print_args(args);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
	{
		args++;
		print_args(args);
	}
	return (0);
}
