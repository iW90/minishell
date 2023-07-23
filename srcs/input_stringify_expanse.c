/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stringify_expanse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:57:00 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/23 19:53:40 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
*/
static t_env	*locate_var(char *str)
{
	int		i;
	char	temp;
	t_env	*found;
	t_ctrl	*ctrl;

	i = 0;
	ctrl = get_control();
	while (str[i] && valid_var_name(str[i]))
		i++;
	temp = str[i];
	str[i] = '\0';
	found = search_var(str, ctrl->env);
	str[i] = temp;
	return (found);
}

static int	expanded_vars_length(char *arg)
{
	int		len;
	t_env	*var;

	len = 0;
	while (*arg)
	{
		if (*arg == '\'' && quote_closes(arg))
			arg += goto_next_quote(arg) + 1;
		if (*arg == '$' && is_a_quoted_var(arg + 1))
		{
			var = locate_var(arg + 1);
			len += (int)ft_strlen(var->value);
			len -= (int)ft_strlen(var->key);
			len--;
		}
		arg++;
	}
	return (len);
}

static void	copy_everything(char *src, char *dst, int size)
{
	int		i;
	t_env	*var;

	i = 0;
	while (i < size && src[i])
	{
		if (src[i] == '\'' && quote_closes(&src[i]))
		{
			*dst++ = src[i++];
			while (src[i] != '\'')
				*dst++ = src[i++];
			*dst++ = src[i++];
		}
		if (src[i] == '$' && is_a_quoted_var(&src[i + 1]))
		{
			var = locate_var(&src[i + 1]);
			ft_memcpy(dst, var->value, ft_strlen(var->value));
			i += (int)ft_strlen(var->key) + 1;
			dst += (int)ft_strlen(var->value);
		}
		else
			*dst++ = src[i++];
	}
	*dst = '\0';
}

char	*copy_with_expanse(char *arg, int len)
{
	int		size;
	char	temp;
	char	*copied;
	char	*new;

	temp = arg[len];
	arg[len] = '\0';
	size = (int)ft_strlen(arg);
	size += expanded_vars_length(arg);
	copied = malloc(sizeof(char) * (size + 1));
	if (!copied)
		return (NULL);
	copy_everything(arg, copied, size);
	arg[len] = temp;
	new = copy_argument(copied, size, 0, 0);
	free(copied);
	return (new);
}
