/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:08:04 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/16 13:37:55 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_full_path(char *path, char *cmd, int path_len, int cmd_len)
{
	char	*full;

	full = malloc(path_len + cmd_len + 2);
	if (!full)
		exit_program(OUT_OF_MEMORY);
	ft_memcpy(full, path, path_len);
	ft_memcpy(full + path_len + 1, cmd, cmd_len);
	full[path_len] = '/';
	full[path_len + cmd_len + 1] = '\0';
	return (full);
}

static char	*check_exec(char *path, char *cmd, int path_len, int cmd_len)
{
	char		*str;
	struct stat	file_status;

	str = get_full_path(path, cmd, path_len, cmd_len);
	if (stat(str, &file_status) == 0)
	{
		if (S_ISREG(file_status.st_mode) && access(str, X_OK) == 0)
			return (str);
		get_control()->status = 126;
	}
	free(str);
	return (NULL);
}

static char	*find_exec(char *path, char *cmd)
{
	struct dirent	*files;
	DIR				*dir;
	char			*full_path;
	size_t			len;

	dir = opendir(path);
	if (!dir)
		return (NULL);
	full_path = NULL;
	files = readdir(dir);
	len = ft_strlen(cmd);
	while (len && files)
	{
		if (!ft_strncmp(cmd, files->d_name, len + 1))
			full_path = check_exec(path, cmd, ft_strlen(path), len);
		if (full_path)
			break ;
		files = readdir(dir);
	}
	closedir(dir);
	return (full_path);
}

static char	*search_dot_dirs(char *cmd)
{
	char	*str;

	if (!cmd || (cmd[0] != '.' && cmd[0] != '/'))
		return (NULL);
	str = NULL;
	if (cmd[0] == '/' && cmd[1])
		str = check_exec(NULL, &cmd[1], 0, ft_strlen(&cmd[1]));
	if (ft_strlen(cmd) < 3)
		return (str);
	if (cmd[0] == '.' && cmd[1] == '/')
		str = check_exec(".", &cmd[2], 1, ft_strlen(&cmd[2]));
	if (ft_strlen(cmd) < 4)
		return (str);
	if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		str = check_exec("..", &cmd[3], 2, ft_strlen(&cmd[3]));
	return (str);
}

char	*get_exec_path(char *env_path, char *cmd)
{
	char	*token;
	char	*str;

	str = search_dot_dirs(cmd);
	if (str)
		return (str);
	if (!env_path)
		return (NULL);
	token = ft_strtok(env_path, ":");
	while (token)
	{
		str = find_exec(token, cmd);
		if (str)
			return (str);
		token = ft_strtok(NULL, ":");
	}
	return (NULL);
}
