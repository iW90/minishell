/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:50:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/08 11:34:11 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_here	*add_heredoc(t_here *head)
{
	t_here	*node;

	node = malloc(sizeof(t_here));
	if (!node)
	{
		free_heredocs(head, 'c');
		exit_program(OUT_OF_MEMORY);
	}
	*node = (t_here){0};
	return (node);
}

t_cli	*add_cli(t_here *head)
{
	t_cli	*node;

	node = malloc(sizeof(t_cli));
	if (!node)
	{
		free_heredocs(head, 'c');
		exit_program(OUT_OF_MEMORY);
	}
	*node = (t_cli){0};
	return (node);
}

t_cli	*remove_cli(t_cli *cli)
{
	t_cli	*next;
	t_cli	*temp;

	if (!cli)
		return (NULL);
	temp = get_control()->commands;
	next = cli->next;
	while (temp && temp->next != cli)
		temp = temp->next;
	if (get_control()->commands == cli)
		get_control()->commands = next;
	else
		temp->next = next;
	if (cli->args)
		clear_pbox(cli->args);
	if (cli->fd[0] > 2)
		close(cli->fd[0]);
	if (cli->fd[1] > 2)
		close(cli->fd[1]);
	free(cli);
	return (next);
}
