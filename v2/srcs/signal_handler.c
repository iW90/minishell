/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:49:23 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/13 21:55:16 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	MODO INTERATIVO
** rl_on_new_line: Move o cursor para uma nova linha
** rl_replace_line: Limpa a linha de entrada atual
** rl_redisplay: Reexibe o prompt
*/
static void	sig_handler(int sig)
{
	t_ctrl	*ctrl;

	if (sig != SIGINT)
		return ;
	ctrl = get_control();
	ft_putstr_fd("\n", STDOUT_FILENO);
	ctrl->status = 130;
	rl_on_new_line();
	rl_replace_line("", STDIN_FILENO);
	rl_redisplay();
}

/*	MODO NÃO INTERATIVO
** Usado quando o minishell está no modo não-interativo,
** o que significa que não está aguardando a entrada do
** usuário. Por exemplo, quando um comando está em execução
** (ou seja, cat), o minishell não deve reagir a SIGINT e
** SIGQUIT porque apenas o processo em execução (cat)
** precisa reagir a esses sinais.
*/
static void	non_interactive_mode(int sig)
{
	t_ctrl	*ctrl;

	ctrl = get_control();
	if (sig == SIGINT)
		ctrl->status = 130;
	if (sig == SIGQUIT)
		ctrl->status = 131;
	if (sig == SIGPIPE)
		exit_program(127 + sig);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	here_docking(int sig)
{
	if (sig == SIGINT)
		exit_program(130);
}

void	set_signals(int mode)
{
	if (mode == ACTIVE)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_DFL);
	}
	if (mode == INACTIVE)
	{
		signal(SIGINT, non_interactive_mode);
		signal(SIGQUIT, non_interactive_mode);
		signal(SIGPIPE, non_interactive_mode);
	}
	if (mode == DEFAULT)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGPIPE, SIG_DFL);
	}
	if (mode == HEREDOC)
		signal(SIGINT, here_docking);
}
