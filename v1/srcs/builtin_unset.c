/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 20:35:40 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/12 20:55:05 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_unset(t_env *env, char **args)
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
