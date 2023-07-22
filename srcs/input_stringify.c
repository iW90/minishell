/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stringify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:18:47 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/22 00:25:32 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_variable(char *src)
{
	t_ctrl	*ctrl;
	t_env	*var;
	char	*str;
	int		len;

	ctrl = get_control();
	var = search_var(src, ctrl->env);
	len = ft_strlen(var->value) + 1;
	str = malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	ft_strlcpy(str, var->value, len);
	return (str);
}

static char	*copy_argument(char *arg, int len, int i)
{
	char	*str;
	int		copychars;

	len = size_minus_quotes(arg, len);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (i < len)
	{
		copychars = 0;
		if (is_quote(*arg))
			copychars += goto_next_quote(arg);
		if (copychars)
		{
			ft_memcpy(&str[i], arg + 1, copychars - 1);
			arg += copychars + 1;
			i += copychars - 1;
		}
		else
			str[i++] = *arg++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_arg(char *args, char **pointers, int done)
{
	static int	current;
	char		*str;
	int			start;

	while (ft_isblank(args[current]))
		current++;
	start = current;
	while (args[current] && !ft_isblank(args[current]))
	{
		if (is_quote(args[current]))
			current += goto_next_quote(&args[current]) + 1;
		else
			current++;
	}
	str = copy_argument(&args[start], current - start, 0);
	if (!str)
	{
		clear_ptr_array(pointers);
		exit_program(OUT_OF_MEMORY);
	}
	if (done)
		current = 0;
	return (str);
}

void	expand_quoted_vars(char **args)
{
	int		i;
	char	*temp;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '$' && is_a_quoted_var(&args[i][1]))
		{
			temp = expand_variable(&args[i][1]);
			if (!temp)
			{
				clear_ptr_array(args);
				exit_program(OUT_OF_MEMORY);
			}
			free(args[i]);
			args[i] = temp;
		}
		i++;
	}
}

char	**stringify_args(char *args)
{
	char	**pointers;
	int		size;
	int		i;

	pointers = NULL;
	if (!args)
		return (NULL);
	size = count_args(args);
	pointers = malloc(sizeof(char *) * (size + 1));
	if (!pointers)
		exit_program(OUT_OF_MEMORY);
	i = 0;
	while (i <= size)
		pointers[i++] = NULL;
	i = 0;
	while (i < size)
	{
		pointers[i] = get_next_arg(args, pointers, i == size - 1);
		i++;
	}
	expand_quoted_vars(pointers);
	return (pointers);
}
