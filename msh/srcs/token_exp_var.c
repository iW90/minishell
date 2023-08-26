/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_exp_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:38:37 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/20 16:28:09 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_special_var(int *i)
{
	(*i)++;
	return (ft_itoa(get_control()->status));
}

static char	*get_empty_var(int *i)
{
	(*i)++;
	return (ft_calloc(1, sizeof(char)));
}

static char	*get_name_var(char *input, int *i)
{
	int		start;
	int		len;
	char	*name;

	start = *i;
	while (input[*i] == '_' || ft_isalnum(input[*i]))
		(*i)++;
	len = *i - start + 1;
	name = malloc(sizeof(char) * len);
	if (!name)
		exit_program(OUT_OF_MEMORY);
	ft_strlcpy(name, &input[start], len);
	return (name);
}

char	*get_var(char *str, int *i)
{
	char	*name;
	t_env	*var;

	name = NULL;
	var = NULL;
	if (!is_var(str[*i]))
		return (NULL);
	if (is_var(str[*i]) == 2)
		return (get_special_var(i));
	if (is_var(str[*i]) == 3)
		return (get_empty_var(i));
	name = get_name_var(str, i);
	var = search_var(name);
	if (name)
		free(name);
	if (!var)
		return (NULL);
	return (ft_strdup(var->value));
}
