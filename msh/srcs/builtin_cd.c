/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:10:09 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/16 19:53:08 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_pwd(char *prefix)
{
	char	current_path[PATH_MAX];
	char	*pwd;

	getcwd(current_path, sizeof(current_path));
	pwd = ft_strjoin(prefix, current_path);
	return (pwd);
}

static void	set_pwd(char *pwd)
{
	t_ctrl	*control;

	control = get_control();
	if (!pwd)
		return ;
	new_var(control->env, pwd);
}

static int	change_directory(const char *path)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = get_pwd("OLDPWD=");
	if (!chdir(path))
	{
		pwd = get_pwd("PWD=");
		set_pwd(pwd);
		set_pwd(old_pwd);
		free(pwd);
		free(old_pwd);
		return (0);
	}
	else
	{
		free(old_pwd);
		perror("cd: ");
		return (1);
	}
}

static int	concat_tilde(char *path, char *home)
{
	char	*full_path;
	int		status;

	path++;
	full_path = ft_strjoin(home, path);
	if (!full_path)
		return (OUT_OF_MEMORY);
	status = change_directory(full_path);
	free(full_path);
	return (status);
}

int	b_cd(char **path)
{
	t_env	*home;

	home = search_var("HOME");
	if (!path || !*path)
	{
		if (!home)
			return (print_builtin_errors("cd: HOME not set\n", 1));
		return (change_directory(home->value));
	}
	else if (path[1])
		return (print_builtin_errors("cd: too many arguments\n", 1));
	else if (!ft_strncmp(*path, "~", 1))
	{
		if (!home)
			return (print_builtin_errors("cd: HOME not set\n", 1));
		if (!ft_strncmp(*path, "~", 2) || !ft_strncmp(*path, "~/", 3))
			return (change_directory(home->value));
		if (!ft_strncmp(*path, "~/", 2))
			return (concat_tilde(*path, home->value));
		return (print_builtin_errors("cd: cannot change directory\n", 1));
	}
	else
		return (change_directory(*path));
}
