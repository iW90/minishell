/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_input_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:28:47 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/09 20:30:56 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cli_list(t_cli *list)
{
	if (!list)
		return ;
	printf("cmd: %s \t//\t Args: %s \t//\t Director: %s\n", list->cmd, list->args, list->director);
	print_cli_list(list->next);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (-1);
	t_cli	*cmd_line = parse_input(av[1]);
	print_cli_list(cmd_line);
}

/*
int	is_builtin(char *str, t_env *env_list)
{
	if (!ft_strncmp(str, "ping\0", 5))
	{
		printf("pong\n");
		return (1);
	}
	if (!ft_strncmp(str, "exit\0", 5))
	{
		clear_var_list(env_list);
		free(str);
		exit(0);
	}
	if (!ft_strncmp(str, "env\0", 4))
	{
		print_var_list(env_list);
		return (1);
	}
	return (0);
}

========

static void	print_args(char **args)
{
	int	i;

	i = 1;
	if (!args)
		return ;
	while (*args)
		printf("[%i]%s\t", i++, *args++);
}

static void	print_cli_list(t_cli *list)
{
	if (!list)
		return ;
	printf("Cmd: %s \t//\t", list->cmd);
	printf("Args: ");
	print_args(list->args);
	printf(" \t//\tDirector: %s\n", list->director);
	print_cli_list(list->next);
}

*/
