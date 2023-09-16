/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 21:02:09 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/16 17:35:08 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*validate_if_var_exist(t_env *list, char *arg)
{
	int	len;

	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	if (!arg[len])
		return (NULL);
	while (list)
	{
		if (!ft_strncmp(arg, list->key, len) && !list->key[len])
			return (list);
		list = list->next;
	}
	return (NULL);
}

void	new_var(t_env *env, char *args)
{
	t_env	*var_to_update;

	var_to_update = validate_if_var_exist(env, args);
	if (!var_to_update)
		add_var(env, args);
	else
		set_var(args, var_to_update);
}

static int	validate_var(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] != '_' && !ft_isalpha(arg[i]))
		return (-1);
	i++;
	while (arg[i] && arg[i] != '=')
		if (arg[i] != '_' && !ft_isalnum(arg[i++]))
			return (-1);
	return (0);
}

int	b_export(t_env *env, char **args)
{
	int	status;

	status = 0;
	if (!args && env)
		return (export_without_args(env->next));
	while (*args)
	{
		if (validate_var(*args))
		{
			ft_putstr_fd("msh: not a valid identifier\n", STDERR_FILENO);
			status = 1;
		}
		else
			new_var(env, *args);
		args++;
	}
	return (status);
}
