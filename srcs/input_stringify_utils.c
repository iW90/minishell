/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stringify_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 00:22:37 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/23 19:46:52 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_key_or_value(t_env *var, char *dst, char *src)
{
	if (!ft_strncmp(var->key, src, ft_strlen(src)) && \
		ft_strncmp(var->key, var->value, ft_strlen(var->value))) 
		*dst++ = '$';
	ft_memcpy(dst, src, ft_strlen(src));
}

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

int	has_expanded_var(char *arg, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (arg[i] == '\'' && quote_closes(&arg[i]))
			i += goto_next_quote(arg);
		if (arg[i] == '$' && is_a_quoted_var(&arg[i + 1]))
			return (1);
		i++;
	}
	return (0);
}
