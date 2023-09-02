/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:25:37 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/26 17:55:49 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_tokens(t_token *token)
{
	if (!token)
		return ;
	clear_tokens(token->next);
	if (token->str)
		free(token->str);
	free(token);
}

void	clear_pbox(char **pbox)
{
	int	i;

	i = -1;
	while (pbox[++i])
		if (pbox[i])
			free(pbox[i]);
	free(pbox);
}

static void	clear_env(t_env *list)
{
	if (!list)
		return ;
	clear_env(list->next);
	if (list->key)
		free(list->key);
	free(list);
}

void	clear_cli(t_cli *cli)
{
	if (!cli)
		return ;
	clear_cli(cli->next);
	if (cli->args)
		clear_pbox(cli->args);
	if (cli->fd[0])
		close(cli->fd[0]);
	if (cli->fd[1])
		close(cli->fd[1]);
	free(cli);
}

void	exit_program(int code)
{
	t_ctrl	*control;

	control = get_control();
	if (control->input)
		free(control->input);
	if (control->env)
		clear_env(control->env);
	if (control->tokens)
		clear_tokens(control->tokens);
	if (control->pbox)
		clear_pbox(control->pbox);
	if (control->commands)
		clear_cli(control->commands);
	rl_clear_history();
	if (code)
		control->status = code;
	exit((unsigned char)control->status);
}
