/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_stringify_expanse.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 14:57:00 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/23 15:40:58 by maalexan         ###   ########.fr       */
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

static t_env	*locate_var(char *str)
{
	int		i;
	char	temp;
	t_env	*found;
	t_ctrl	*ctrl;

	i = 0;
	ctrl = get_control();
	while (str[i] && !ft_isblank(str[i]))
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
		if (*arg == '\'')
			arg += goto_next_quote(arg) + 1;
		if (*arg == '$' && is_a_quoted_var(*(arg + 1)))
		{
			var = locate_var(arg);
			len += (int)ft_strlen(var->value);
            len -= (int)ft_strlen(var->key);
            len--;
		}
		arg++;
	}
	return (len);
}

char	*copy_with_expanse(char *arg, int len)
{
	int		i;
	int		size;
	char	temp;
    char    *copied;

	i = 0;
	temp = arg[len];
    arg[len] = '\0';
    size = (int)ft_strlen(arg);
	size += count_expanded_vars(arg);
    copied = malloc(sizeof(char) * (size + 1));
    if (!copied)
		return (NULL);
    copied[size] = '\0';
    while (i < size)
    {
        if (arg[i] == '\'' && quote_closes(arg[i]))
            copy_everything()
                
    }
    arg[len] = temp;

}
