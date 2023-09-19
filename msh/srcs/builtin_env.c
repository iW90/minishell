/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:25:59 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/16 19:53:48 by inwagner         ###   ########.fr       */
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

int	b_env(char **path, t_env *list)
{
	t_env	*head;

	if (path)
		return (print_builtin_errors("env: too many arguments\n", 1));
	head = list;
	list = list->next;
	while (list)
	{
		if (list->value)
			print_env(list->key, list->value);
		list = list->next;
	}
	print_env(head->key, head->value);
	return (0);
}
