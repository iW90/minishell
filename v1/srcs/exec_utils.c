/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 17:23:08 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/09 17:23:11 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* VERIFICA SE É EXEC
 */
int	is_exec(char *path, char *cmd)
{
	t_ctrl	*ctrl;
	char	*temp_path;
	size_t	len;

	if (!cmd)
		return (0);
	ctrl = get_control();
	if (path)
	{
		len = ft_strlen(path);
		temp_path = malloc(sizeof(char) * len + 1);
		if (!temp_path)
			exit_program(OUT_OF_MEMORY);
		ft_strlcpy(temp_path, path, len);
		ctrl->exec_path = parse_path(temp_path, cmd);
		free(temp_path);
	}
	else
		ctrl->exec_path = parse_path(NULL, cmd);
	if (ctrl->exec_path)
		return (1);
	return (0);
}
