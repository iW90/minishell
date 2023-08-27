/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 21:10:09 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/22 19:34:57 by inwagner         ###   ########.fr       */
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

/* ERROS POSSÍVEIS DO COMANDO "Change Directory"

	"Home directory not set": Ocorre quando o diretório inicial do usuário (home
	directory) não está configurado corretamente.

	"Too many arguments": Indica que foram fornecidos argumentos extras com o
	comando cd. O cd aceita apenas um único argumento, que é o diretório para o
	qual se deseja mudar.
	
	____________________
	"No such file or directory": Indica que o diretório especificado não existe.
	
	"Permission denied": Significa que o usuário atual não tem permissão para
	acessar o diretório desejado.
	
	"Not a directory": O caminho fornecido para o cd não aponta para um
	diretório válido, mas sim para um arquivo ou outro tipo de objeto do sistema.

	"Too many symbolic links": Refere-se a um loop de links simbólicos, onde o
	caminho contém um número excessivo de referências simbólicas que levam a uma
	recursão infinita.

	"Invalid option": Indica que uma opção inválida foi fornecida juntamente com
	o comando cd. Geralmente, o cd não aceita opções em muitos shells, mas isso
	pode variar dependendo do ambiente.

	"Not a valid directory": Significa que o caminho especificado não corresponde
	a um diretório válido no sistema de arquivos.

	"Read-only file system": Ocorre quando o sistema de arquivos em que o
	diretório está localizado está montado apenas para leitura. Nesse caso, não
	é possível navegar para outros diretórios.

	____________________
	-1 na saída do 'chdir' indica que ocorreu um erro ao tentar mudar de diretório.
	Nesse caso, você pode usar a variável errno para obter mais informações sobre o
	erro específico. Alguns possíveis valores de errno associados ao chdir incluem:

		ENOENT (No such file or directory): O diretório especificado não existe.
		EACCES (Permission denied): O usuário não tem permissão de acesso ao dir.
		ENOTDIR (Not a directory): O caminho fornecido não é um diretório válido.
		EFAULT (Bad address): O ponteiro para o caminho do diretório é inválido.
		EROFS (Read-only file system): O diretório é somente de leitura.
		ENOENT (No such file or directory): Indica que o diretório especificado
			não existe.
		ELOOP (Too many symbolic links): Número excessivo de referências simbólicas
			(recursão infinita).
		EIO (Input/output error): Indica um erro de entrada/saída genérico que pode
			ocorrer ao acessar o diretório.
*/