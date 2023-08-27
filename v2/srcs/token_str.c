/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:35:22 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/27 11:20:14 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*set_quoted_token(char *input, int *i)
{
	int		start;
	int		len;
	char	*str;

	start = *i + 1;
	get_quote(input, i);
	(*i)++;
	len = (*i) - start;
	str = copy_str(input, start, len);
	return (str);
}

static char	*get_unquote(char *input, int *i)
{
	int		start;
	int		len;
	char	*str;

	start = *i;
	while (input[*i] && \
			!ft_isblank(input[*i]) && \
			!is_bracket(input[*i]) && \
			!is_quote(input[*i]) && \
			!is_pipe(input[*i]))
		(*i)++;
	len = (*i) - start + 1;
	str = copy_str(input, start, len);
	return (str);
}

static char	**get_str(char *input, int *i)
{
	t_ctrl	*control;
	char	quote;

	quote = 0;
	if (is_quote(input[*i]))
		quote = input[*i];
	control = get_control();
	control->pbox = malloc(5 * sizeof(char *));
	if (!control->pbox)
		exit_program(OUT_OF_MEMORY);
	null_pbox(control->pbox, 5);
	if (quote == '"')
		control->pbox[3] = set_quoted_token(input, i);
	else
		control->pbox[3] = get_unquote(input, i);
	return (control->pbox);
}

char	*set_expanded_token(char *input, int *i)
{
	char	*str;
	char	**pbox;
	int		j;

	j = 0;
	pbox = get_str(input, i);
	while (has_var(&pbox[3][j]))
		pbox[3] = expand_token(pbox, &j);
	str = pbox[3];
	pbox[3] = NULL;
	clear_pbox(pbox);
	get_control()->pbox = NULL;
	return (str);
}
