/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expand_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 21:13:56 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/23 19:24:17 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Bash variable names can only have alpha numeric 
**	characters or an underscore "_" but there is a 
**	special variable "$?" that must be treated
*/
int	valid_var_name(char c)
{
	return (c == '?' || ft_isalnum(c) || c == '_');
}

/*
**	Checks if an environment variable has quotes
**	within it's composition, so they can be expanded
**	AFTER being tokenized
*/
char	*var_has_quote(t_env *env_var)
{
	char	*cursor;

	cursor = env_var->value;
	while (*cursor)
		if (is_quote(*cursor++))
			return (env_var->key);
	return (env_var->value);
}

/*
**	Verifies if the received string has
**	unclosed quotes, to enable adequate
**	treatment as necessary
**/
int	quote_closes(char *str)
{
	char	quote;

	if (*str != '\'' && *str != '"')
		return (0);
	quote = *str++;
	while (*str && *str != quote)
		str++;
	return (*str == quote);
}

/*
**	Confirms that the string is an
**	environment variable and that
**	it's composition has quotes
**/
int	is_a_quoted_var(char *str)
{
	t_ctrl	*ctrl;
	t_env	*var;
	char	*cursor;
	int		i;
	char	temp;

	i = 0;
	ctrl = get_control();
	while (str[i] && valid_var_name(str[i]))
		i++;
	temp = str[i];
	str[i] = '\0';
	var = search_var(str, ctrl->env);
	str[i] = temp;
	if (!var)
		return (0);
	cursor = var->value;
	while (*cursor)
		if (is_quote(*cursor++))
			return (1);
	return (0);
}

/*
**	Acessory function to help
**	copy the whole quoted string
*/

int	goto_next_quote(char *args)
{
	int		i;
	char	quote;

	i = 1;
	if (!quote_closes(args))
		return (0);
	quote = *args++;
	while (*args++ != quote)
		i++;
	return (i);
}
