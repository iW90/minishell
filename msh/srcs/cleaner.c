/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 10:25:37 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/14 20:11:12 by inwagner         ###   ########.fr       */
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
	t_cli	*next_cli;

	if (!cli)
		return ;
	next_cli = cli->next;
	if (cli->args)
		clear_pbox(cli->args);
	if (cli->fd[0] > 0)
		close(cli->fd[0]);
	if (cli->fd[1] > 0)
		close(cli->fd[1]);
	free(cli);
	clear_cli(next_cli);
}

void	exit_program(int code)
{
	t_ctrl	*control;
	int		i;

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
	i = -1;
	while (++i < FD_MAX)
		close(i);
	exit((unsigned char)control->status);
}
