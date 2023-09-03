/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 14:50:25 by maalexan          #+#    #+#             */
/*   Updated: 2023/09/02 20:59:48 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_here	*make_new_heredoc(t_here *head)
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

t_cli	*make_new_cli(t_here *head)
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

static void	clear_node(t_cli *cli)
{
	if (cli->args)
		clear_pbox(cli->args);
	if (cli->fd[0] > 2)
		close(cli->fd[0]);
	if (cli->fd[1] > 2)
		close(cli->fd[1]);
	free(cli);
}

t_cli	*remove_cli(t_cli *cli)
{
	t_cli	*next;
	t_cli	*temp;

	if (!cli)
		return (NULL);
	temp = get_control()->commands;
	next = cli->next;
	while (temp->next != cli)
		temp = temp->next;
	if (get_control()->commands == cli)
		get_control()->commands = next;
	else
		temp->next = next;
	clear_node(cli);
	return (next);
}

t_token *discard_tokens(t_token *tok)
{
	if (!tok)
		return NULL;

	t_token *current = tok;
	t_token *prev_boundary = NULL;
	t_token *next_boundary = NULL;

	while (current->prev && current->prev->type != PIPE)
		current = current->prev;
	prev_boundary = current->prev;
	current = tok;
	while (current->next && current->next->type != PIPE)
		current = current->next;
	next_boundary = current->next;
	if (next_boundary && next_boundary->type == PIPE)
	{
		t_token *tmp = next_boundary->next;
		remove_token(next_boundary);
		next_boundary = tmp;
	}
	current = tok;
	while (current != next_boundary)
	{
		t_token *tmp = current->next;
		remove_token(current);
		current = tmp;
	}
	if (prev_boundary)
		prev_boundary->next = next_boundary;
	if (next_boundary)
		next_boundary->prev = prev_boundary;
	return next_boundary;
}
