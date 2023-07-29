/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 19:38:31 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/29 14:51:02 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *msg, char *refstr, char refchar)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (refstr)
		ft_putstr_fd(refstr, STDERR_FILENO);
	if (refchar)
		ft_putchar_fd(refchar, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
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
	int	j;

	j = *i;
	if (j)
		j--;
	while (ft_isblank(input[j]) && j)
		j--;
	if (!is_pipe(input[j]) && !ft_isblank(input[j]))
		return (0);
	print_error("syntax error near unexpected token `", NULL, '|');
	return (-1);
}

int	validate_single_brackets(char *input)
{
	int	i;

	i = 0;
	while (input[i + 1])
		i++;
	while (ft_isblank(input[i]))
		i--;
	if (!is_bracket(input[i]))
		return (0);
	print_error("syntax error near unexpected token `", "newline", 0);
	return (1);
}

static int	validate_brackets(char *input, int *i)
{
	char	c;

	if (validate_single_brackets(input))
		return (1);
	c = input[(*i)++];
	if (input[*i] != c || !input[*i])
	{
		(*i)--;
		return (0);
	}
	(*i)++;
	while (ft_isblank(input[*i]))
		(*i)++;
	if (!(is_pipe(input[*i]) || is_bracket(input[*i]) || !input[*i]))
	{
		return (0);
	}
	c = input[*i];
	if (!c)
		print_error("syntax error near unexpected token `", "newline", 0);
	else if (is_pipe(c) || is_bracket(c))
		print_error("syntax error near unexpected token `", NULL, c);
	return (-1);
}

int	bar_input(char *input)
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
