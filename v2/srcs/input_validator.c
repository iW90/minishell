/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:38:31 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/21 18:07:05 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(char *msg, char *refstr, char refchar)
{
	ft_putstr_fd("msh: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (refstr)
		ft_putstr_fd(refstr, STDERR_FILENO);
	if (refchar)
		ft_putchar_fd(refchar, STDERR_FILENO);
	if (refstr || refchar)
		ft_putstr_fd("'", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

static int	check_unclosed_quotes(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	get_quote(input, i);
	if (input[*i])
		return (0);
	print_error("unable to find matching `", NULL, quote);
	return (-1);
}

static int	validate_pipe(char *input, int *i)
{
	if (is_bracket(input[*i + 1]))
		(*i)++;
	if (input[*i + 1] == input[*i] && !is_pipe(input[*i]))
		(*i)++;
	(*i)++;
	while (input[*i] && ft_isblank(input[*i]))
		(*i)++;
	if (is_pipe(input[*i]) || is_bracket(input[*i]))
		return (print_error("syntax error near unexpected token `", \
				NULL, input[*i]));
	(*i)--;
	return (0);
}

static int	validate_brackets(char *input, int *i)
{
	if (input[*i + 1] == input[*i])
		(*i)++;
	(*i)++;
	while (input[*i] && ft_isblank(input[*i]))
		(*i)++;
	if (!input[*i])
		return (print_error("syntax error near unexpected token `", \
				"newline", 0));
	if (is_pipe(input[*i]) || is_bracket(input[*i]))
		return (print_error("syntax error near unexpected token `", \
				NULL, input[*i]));
	(*i)--;
	return (0);
}

int	validate_input(char *input)
{
	int	i;

	if (!input)
		return (0);
	i = -1;
	while (input[++i])
	{
		if (is_quote(input[i]))
			if (check_unclosed_quotes(input, &i))
				return (-1);
		if (input[i] && is_pipe(input[i]))
			if (validate_pipe(input, &i))
				return (-1);
		if (input[i] && is_bracket(input[i]))
			if (validate_brackets(input, &i))
				return (-1);
	}
	return (0);
}
