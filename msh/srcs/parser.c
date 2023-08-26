/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 18:29:33 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/21 20:10:12 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_cmd(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == BUILTIN || token->type == EXEC || token->type == ARGUMENT);
}

static enum e_type	set_exec(t_token *token, char *execpath)
{
	free(token->str);
	token->str = execpath;
	return (EXEC);
}

static enum e_type	get_type(t_token *token)
{
	char	*execpath;
	char	*path;
	t_env	*envpath;

	if (is_builtin(token->str))
		return (BUILTIN);
	path = NULL;
	envpath = search_var("PATH");
	if (envpath)
	{
		path = ft_strdup(envpath->value);
		if (!path)
			exit_program(OUT_OF_MEMORY);
	}
	execpath = get_exec_path(path, token->str);
	if (path)
		free(path);
	if (execpath)
		return (set_exec(token, execpath));
	return (ARGUMENT);
}

static void	set_type(t_token *token)
{
	if (!is_cmd(token->prev))
		token->type = get_type(token);
	else
		token->type = ARGUMENT;
}

int	parser(void)
{
	t_token	*tokens;

	tokens = get_control()->tokens;
	if (!tokens)
		return (0);
	if (!tokens->type)
		set_type(tokens);
	tokens = tokens->next;
	while (tokens)
	{
		if (tokens->type)
		{
			tokens = tokens->next;
			continue ;
		}
		set_type(tokens);
		tokens = tokens->next;
	}
	return (1);
}
