/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:02:09 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/08 22:14:32 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*validate_if_var_exist(t_env *list, char *arg)
{
	int	len;

	len = ft_strlen(arg);
	while (list)
	{
		if (!ft_strncmp(arg, list->key, len) && !list->key[len])
			return (list);
		list = list->next;
	}
	return (NULL);
}

static void	new_var(t_env *env, char *args)
{
	t_env	*var_to_update;

	var_to_update = validate_if_var_exist(env, args);
	if (!var_to_update)
		add_var(env, args);
	else
		set_var(args, var_to_update);
}

void	b_export(t_env *env, char **args)
{
	if (!args)
		return ;
	while (*args)
	{
		new_var(env, *args);
		args++;
	}
}
