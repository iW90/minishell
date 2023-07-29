/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 10:14:08 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/29 11:19:48 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function receives the variable name and it's intended 
**	length, and looks for a match in the envp list.
**	In order to be able to guarantee a match, the original
**	string's first char after the variable name is temporary
**	replaced by a null char, which is returned afterwards
*/
static int	assess_len(char *str, int len, char **copy)
{
	t_ctrl	*control;
	t_env	*var;
	char	*src;
	char	temp;

	if (!*str || !len)
		return (0);
	src = NULL;
	control = get_control();
	temp = str[len];
	str[len] = '\0';
	var = search_var(str, control->env);
	if (var)
		src = var_has_quote(var);
	str[len] = temp;
	if (copy && src)
		copy_key_or_value(var, *copy, src);
	if (src && ft_strncmp(var->key, var->value, ft_strlen(var->value)) \
		&& !ft_strncmp(var->key, src, ft_strlen(src)))
		return (ft_strlen(src) + 1);
	else if (src)
		return (ft_strlen(src));
	return (0);
}

/*
**	Once the indication of a variable is found ("$" char)
**	this function runs through it's valid chars to find
**	out the intended name, and return it's expanded length,
**	or zero in case there is no matches in the environment
*/
static int	expand_var(char *line, int *i, char **copy)
{
	char	*start;
	int		len;

	(*i)++;
	start = &line[*i];
	len = 1;
	if (ft_isdigit(*start))
		(*i)++;
	else if (*start == '?')
		return (special_var_treat(copy, i));
	else
		while (ft_isalnum(line[*i]) || line[*i] == '_')
			(*i)++;
	len = assess_len(start, &line[*i] - start, copy);
	return (len);
}

static int	copy_between_quotes(char *line, int *i, char **dst)
{
	**dst = line[*i];
	(*i)++;
	*dst += 1;
	while (line[*i] != '\'')
	{
		**dst = line[*i];
		*dst += 1;
		(*i)++;
	}
	**dst = line[*i];
	(*i)++;
	*dst += 1;
	return (1);
}

/*
**	Once the length has been assessed, this function will
**	then copy the variable (if it exists), so it can provide
**	an expanded version of the captured readline
*/
char	*copy_expansion(char *line, int len)
{
	char	*expanded;
	int		i;
	int		quoted;
	char	*cursor;

	i = 0;
	expanded = malloc(sizeof(char) * len);
	if (!expanded)
		exit_program(OUT_OF_MEMORY);
	cursor = expanded;
	while (line[i])
	{
		quoted = 0;
		if (line[i] == '$' && line[i + 1] == '\'')
			i++;
		if (line[i] == '\'' && quote_closes(&line[i]))
			quoted = copy_between_quotes(line, &i, &cursor);
		if (!quoted && line[i] == '$' && valid_var_name(line[i + 1]))
			cursor += expand_var(line, &i, &cursor);
		else if (line[i])
			*cursor++ = line[i++];
	}
	*cursor = '\0';
	return (expanded);
}

/*
**	Checks the line taken from prompt in order to 
**	expand variables indicated by $.
**	This first part is responsible to calculate the
**	total length of the string to inform it to malloc
*/
char	*expand_line(char *line)
{
	int		i;
	int		total_len;

	i = 0;
	total_len = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '\'')
			i++;
		if (line[i] == '\'' && quote_closes(&line[i]))
			total_len += get_quote(line, &i);
		if (line[i] == '$' && valid_var_name(line[i + 1]))
			total_len += expand_var(line, &i, NULL);
		else if (line[i])
		{
			total_len++;
			i++;
		}
	}
	if (total_len)
		return (copy_expansion(line, total_len + 1));
	return (NULL);
}
