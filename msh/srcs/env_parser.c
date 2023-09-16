/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 09:34:50 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/16 13:35:13 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_var(const char *src, t_env *node)
{
	int		len;
	char	*dst;
	char	*c;

	if (node->key)
		free (node->key);
	len = ft_strlen(src) + 1;
	dst = malloc(sizeof(char) * len);
	if (!dst)
		exit_program(OUT_OF_MEMORY);
	ft_strlcpy(dst, src, len);
	c = ft_strchr(dst, '=');
	if (c)
	{
		*c = '\0';
		node->value = ++c;
	}
	node->key = dst;
}

t_env	*add_var(t_env *prev, char *var)
{
	t_env	*newnode;

	if (prev)
		while (prev->next)
			prev = prev->next;
	newnode = malloc(sizeof(t_env));
	if (!newnode)
		exit_program(OUT_OF_MEMORY);
	*newnode = (t_env){0};
	if (prev)
		prev->next = newnode;
	set_var(var, newnode);
	return (newnode);
}

t_env	*search_var(char *var)
{
	t_env	*env;
	int		size;

	env = get_control()->env;
	size = ft_strlen(var) + 1;
	while (env)
	{
		if (!ft_strncmp(var, env->key, size))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*remove_var(char *str, t_env *list)
{
	t_env	*prev;
	t_env	*current;

	if (!str || !list)
		return (list);
	prev = NULL;
	current = list;
	while (current)
	{
		if (!ft_strncmp(str, "_", 2))
			break ;
		if (!ft_strncmp(str, current->key, ft_strlen(str) + 1))
		{
			if (prev == NULL)
				list = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
	return (list);
}

t_env	*parse_env(char **env)
{
	t_env	*env_list;
	t_env	*prev_env;

	env_list = add_var(NULL, *env++);
	prev_env = env_list;
	while (*env)
	{
		prev_env = add_var(prev_env, *env);
		env++;
	}
	return (env_list);
}
