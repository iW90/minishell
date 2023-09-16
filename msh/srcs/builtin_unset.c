/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 20:35:40 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/21 20:42:24 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(char **args, t_env *env)
{
	if (!args)
		return (0);
	while (*args)
	{
		remove_var(*args, env);
		args++;
	}
	return (0);
}
