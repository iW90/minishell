/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:25:59 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/28 18:23:01 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env(char *key, char *value)
{
	ft_putstr_fd(key, STDOUT_FILENO);
	ft_putstr_fd("=", STDOUT_FILENO);
	ft_putstr_fd(value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	print_export(char *key, char *value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	ft_putstr_fd("=\"", STDOUT_FILENO);
	ft_putstr_fd(value, STDOUT_FILENO);
	ft_putstr_fd("\"\n", STDOUT_FILENO);
}

int	b_env(char **path, t_env *list, int exp)
{
	t_env	*head;

	if (path)
		return (ft_putstr_fd("env: too many arguments\n", STDERR_FILENO), 1);
	head = list;
	list = list->next;
	while (list)
	{
		if (!exp)
			print_env(list->key, list->value);
		else
			print_export(list->key, list->value);
		list = list->next;
	}
	if (!exp)
		print_env(head->key, head->value);
	return (0);
}
