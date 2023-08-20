/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:20:08 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/19 11:19:28 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	return (\
		!ft_strncmp(cmd, "ping", 5) || \
		!ft_strncmp(cmd, "cd", 3) || \
		!ft_strncmp(cmd, "pwd", 4) || \
		!ft_strncmp(cmd, "echo", 5) || \
		!ft_strncmp(cmd, "unset", 6) || \
		!ft_strncmp(cmd, "export", 7) || \
		!ft_strncmp(cmd, "env", 4) || \
		!ft_strncmp(cmd, "exit", 5));
}

int	is_redirector(char *red)
{
	if (ft_strcmp(red, ">>"))
		return (APPEND);
	if (ft_strcmp(red, "<<"))
		return (HEREDOC);
	if (ft_strcmp(red, ">"))
		return (OVERWRITE);
	if (ft_strcmp(red, "<"))
		return (INPUT);
	if (ft_strcmp(red, "|"))
		return (PIPE);
	return (0);
}

int	is_var(char var)
{
	if (!var)
		return (0);
	if (var == '_' || ft_isalpha(var))
		return (1);
	if (var == '?')
		return (2);
	if (ft_isdigit(var))
		return (3);
	return (0);
}

int	is_quote(char quote)
{
	if (quote == '\'')
		return (1);
	if (quote == '"')
		return (2);
	return (0);
}
