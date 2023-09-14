/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:20:34 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/14 19:28:40 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_bracket(char c)
{
	return (c == '>' || c == '<');
}

int	is_pipe(char c)
{
	return (c == '|');
}

int	print_error(char *msg, char *refstr, char refchar)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (refstr)
		ft_putstr_fd(refstr, STDERR_FILENO);
	if (refchar)
		ft_putchar_fd(refchar, STDERR_FILENO);
	if (refstr || refchar)
		ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}
