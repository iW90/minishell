/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:10:09 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/27 17:09:54 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* RETORNA O DIRETÓRIO ATUAL
*/
char	*get_pwd(char *prefix)
{
	char	current_path[PATH_MAX];
	char	*pwd;

	getcwd(current_path, sizeof(current_path));
	pwd = ft_strjoin(prefix, current_path);
	return (pwd);
}

/* ATUALIZA A VARIÁVEL COM O DIRETÓRIO INFORMADO
*/
void	set_pwd(char *pwd)
{
	t_ctrl	*control;

	control = get_control();
	if (!pwd)
		return ;
	new_var(control->env, pwd);
}

/* MUDA O DIRETÓRIO PARA O CAMINHO INFORMADO.
** Para atualizar o PWD e o OLDPWD é necessário pegar o diretório
** antes e depois da mudança de diretório.
*/
int	change_directory(const char *path)
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
		ft_putstr_fd("cd: cannot change directory\n", STDERR_FILENO);
		return (1);
	}
}

/* CONCATENA HOME COM O RESTANTE DO CAMINHO
*/
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
			return (ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO), 1);
		return (change_directory(home->value));
	}
	else if (path[1])
		return (ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO), 1);
	else if (!ft_strncmp(*path, "~", 1))
	{
		if (!home)
			return (ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO), 1);
		if (!ft_strncmp(*path, "~", 2) || !ft_strncmp(*path, "~/", 3))
			return (change_directory(home->value));
		if (!ft_strncmp(*path, "~/", 2))
			return (concat_tilde(*path, home->value));
		return (ft_putstr_fd("cd: cannot change directory\n", STDERR_FILENO), 1);
	}
	else
		return (change_directory(*path));
}
