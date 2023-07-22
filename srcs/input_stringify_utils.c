/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stringify_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 00:22:37 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/22 00:24:47 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char *args)
{
	int	count;

	count = 0;
	while (ft_isblank(*args))
		args++;
	while (*args)
	{
		if (is_quote(*args))
			args += goto_next_quote(args) + 1;
		else
			args++;
		if (ft_isblank(*args) || !*args)
			count++;
		while (ft_isblank(*args))
			args++;
	}
	return (count);
}

int	size_minus_quotes(char *arg, int len)
{
	int	i;
	int	temp;

	i = 0;
	while (i < len)
	{
		temp = 0;
		if (is_quote(arg[i]))
			temp += goto_next_quote(&arg[i]);
		if (temp)
		{
			i += temp;
			len -= 2;
		}
		i++;
	}
	return (len);
}
