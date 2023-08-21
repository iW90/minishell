/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 13:50:16 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/12 18:39:18 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_value(char *value, t_env *env_list)
{
	char	*list_value;
	t_env	*env_node;

	list_value = NULL;
	env_node = NULL;
	env_node = search_var(value, env_list);
	if (env_node)
		list_value = env_node->value;
	return (list_value);
}

static int	count_list(t_env *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list = list->next;
		i++;
	}
	return (i);
}

static char	*copy_to_env(char *key, char *value)
{
	char	*new_var;
	int		key_len;
	int		val_len;

	key_len = ft_strlen(key) + 1;
	val_len = ft_strlen(value) + 1;
	new_var = malloc(sizeof(char) * (key_len + val_len));
	if (!new_var)
		return (NULL);
	ft_strlcpy(new_var, key, key_len);
	ft_strlcpy(new_var + key_len, value, val_len);
	new_var[key_len - 1] = '=';
	return (new_var);
}

char	**stringify_env(t_env *list)
{
	char	**env;
	int		i;
	int		len;

	i = 0;
	len = count_list(list);
	env = malloc(sizeof(char *) * (len + 1));
	if (!env)
		return (NULL);
	while (i < len)
	{
		env[i] = copy_to_env(list->key, list->value);
		if (!env[i++])
			return (NULL);
		list = list->next;
	}
	env[i] = NULL;
	return (env);
}
