/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:56:32 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/02 11:20:20 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export(char *key)
{
	if (!key)
		return ;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(key, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	export_without_args(t_env *env)
{
	char	**envbox;
	char	**envhdr;
	int		n;

	if (!env)
		return (0);
	envbox = stringify_env(env, 1);
	envhdr = envbox;
	n = 0;
	while (envbox[n])
		n++;
	if (!n)
		return (0);
	if (!envbox)
		return (1);
	quick_sort(envbox, 0, n - 1);
	while (*envbox)
		print_export(*envbox++);
	clear_pbox(envhdr);
	return (0);
}
