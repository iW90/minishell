/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shifter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:50:16 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/29 15:27:02 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*last_input(char **argv, char *cmd)
{
	char	*cursor;

	if (!argv)
		return (cmd);
	cursor = *argv;
	while (*(++argv))
		cursor = *argv;
	return (cursor);
}

static t_env	*new_underscore(char **argv, char *cmd)
{
	t_env	*underscore;
	int		len;
	char	*last;

	last = last_input(argv, cmd);
	underscore = malloc(sizeof(t_env));
	if (!underscore)
		exit_program(OUT_OF_MEMORY);
	*underscore = (t_env){0};
	len = ft_strlen(last) + 3;
	underscore->key = malloc(sizeof(char) * len);
	if (!underscore->key)
	{
		free(underscore);
		exit_program(OUT_OF_MEMORY);
	}
	ft_memcpy(underscore->key, "_\0", 2);
	underscore->value = &underscore->key[2];
	ft_memcpy(underscore->value, last, len - 2);
	return (underscore);
}

static t_env	*update_underscore(t_env *head, char **argv, char *cmd)
{
	t_env	*prev;
	t_env	*cursor;

	if (!head || (!argv && !cmd))
		return (NULL);
	cursor = head;
	prev = NULL;
	while (cursor && ft_strncmp("_\0", cursor->key, 2))
	{
		prev = cursor;
		cursor = cursor->next;
	}
	if (cursor)
	{
		if (prev)
			prev->next = cursor->next;
		else
			head = cursor->next;
		free(cursor->key);
		free(cursor);
	}
	cursor = new_underscore(argv, cmd);
	cursor->next = head;
	return (cursor);
}

void	update_env(char **argv, char *cmd, char *exec)
{
	t_ctrl	*control;

	if (!argv && !cmd && !exec)
		return ;
	control = get_control();
	if (exec)
		control->env = update_underscore(control->env, argv, exec);
	else
		control->env = update_underscore(control->env, argv, cmd);
}
