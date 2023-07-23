/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stringify.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 16:18:47 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/23 19:53:32 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*copy_argument(char *arg, int len, int i, int first)
{
	char	*str;
	int		copychars;

	if (first && has_expanded_var(arg, len))
		return (copy_with_expanse(arg, len));
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
	str = copy_argument(&args[start], current - start, 0, 1);
	if (!str)
	{
		clear_ptr_array(pointers);
		exit_program(OUT_OF_MEMORY);
	}
	if (done)
		current = 0;
	return (str);
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
	return (pointers);
}
