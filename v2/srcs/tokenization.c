/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 21:43:06 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/13 00:27:40 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*set_quoted_token(char *input, t_token *token, int *i)
{
	int		start;
	int		end;
	int		len;

	if (input[*i] != '"')
		token->quote = SINGLE;
	else
		token->quote = DOUBLE;
	start = *i + 1;
	get_quote(input, i);
	end = (*i)++;
	len = end - start + 1;
	token->str = malloc(sizeof(char) * len);
	if (!token->str)
		exit_program(OUT_OF_MEMORY);
	ft_strlcpy(token->str, &input[start], len);
	return (token);
}

t_token	*set_unquoted_token(char *input, t_token *token, int *i)
{
	int		start;
	int		end;
	int		len;

	start = *i;
	while (input[*i] && !ft_isblank(input[*i]))
		(*i)++;
	end = *i;
	len = end - start + 1;
	token->str = malloc(sizeof(char) * len);
	if (!token->str)
		exit_program(OUT_OF_MEMORY);
	ft_strlcpy(token->str, &input[start], len);
	return (token);
}

t_token	*get_token(char *input, int *i)
{
	t_token	*new;

	while (input[*i] && ft_isblank(input[*i]))
		(*i)++;
	if (!input[*i])
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		exit_program(OUT_OF_MEMORY);
	*new = (t_token){0};
	if (is_quote(input[*i]))
		return (set_quoted_token(input, new, i));
	else
		return (set_unquoted_token(input, new, i));
}

void	link_token(t_token *new, t_token *last)
{
	if (!new || !last)
		return ;
	while (last->next)
		last = last->next;
	last->next = new;
	new->prev = last;
}

int	tokenization(char *input)
{
	t_ctrl	*control;
	t_token	*current;
	int		i;

	if (!input)
		return (0);
	i = 0;
	control = get_control();
	control->tokens = get_token(input, &i);
	if (!control->tokens)
		return (0);
	while (input[i])
	{
		current = get_token(input, &i);
		link_token(current, control->tokens);
	}
	return (0);
}
