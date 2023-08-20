/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_setter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 09:37:46 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/20 17:55:27 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_pipe_token(char *input, int *i, t_token *token)
{
	token->type = is_redirector("|");
	return (copy_str(input, (*i)++, 2));
}

char	*set_redirector_token(char *input, int *i, t_token *token)
{
	char	*str;
	int		start;
	int		len;

	start = *i;
	if (input[*i + 1] == input[*i])
		(*i)++;
	(*i)++;
	len = *i - start + 1;
	str = copy_str(input, start, len);
	token->type = is_redirector(str);
	return (str);
}

static char	*get_str_token(char *input, int *i)
{
	if (input[*i] == '\'')
		return (set_quoted_token(input, i));
	else
		return (set_expanded_token(input, i));
}

char	*set_str_token(char *input, int *i)
{
	char	*str1;
	char	*str2;
	char	*full;

	str1 = NULL;
	while (input[*i] && \
			!ft_isblank(input[*i]) && \
			!is_bracket(input[*i]) && \
			!is_pipe(input[*i]))
	{
		full = get_str_token(input, i);
		if (!str1)
			str1 = full;
		else if (full)
		{
			str2 = full;
			full = ft_strjoin(str1, str2);
			free(str1);
			free(str2);
		}
	}
	return (full);
}
