/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:20:34 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/09 17:23:38 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* VERIFICA SE É QUOTE
 * Comportamento do bash quando não encontra fechamento do quote:
 * 	bash: unexpected EOF while looking for matching quote.
 * 	bash: syntax error: unexpected end of file
 */
int	is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

/* VERIFICA SE É MAIOR/MENOR
 */
int	is_bracket(char c)
{
	return (c == '>' || c == '<');
}

/* VERIFICA SE É PIPE
 */
int	is_pipe(char c)
{
	return (c == '|');
}

/* VERIFICA SE É REDIRECIONADOR
 */
int	is_redirector(char *red)
{
	return (\
		!ft_strncmp(red, ">>", 2) || \
		!ft_strncmp(red, "<<", 2) || \
		!ft_strncmp(red, ">", 1) || \
		!ft_strncmp(red, "<", 1) || \
		!ft_strncmp(red, "|", 1));
}

/* VERIFICA SE É BUILTIN
 */
int	is_builtin(char *cmd)
{
	return (\
		!ft_strncmp(cmd, "ping\0", 5) || \
		!ft_strncmp(cmd, "cd\0", 3) || \
		!ft_strncmp(cmd, "pwd\0", 4) || \
		!ft_strncmp(cmd, "echo\0", 5) || \
		!ft_strncmp(cmd, "unset\0", 6) || \
		!ft_strncmp(cmd, "export\0", 7) || \
		!ft_strncmp(cmd, "env\0", 4) || \
		!ft_strncmp(cmd, "exit\0", 5));
}
