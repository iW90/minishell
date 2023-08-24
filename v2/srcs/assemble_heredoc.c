/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 16:40:35 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/24 16:48:36 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	Pauses the program execution to 
**	receive the user's input and writes
**	it to an fd while it's open
*/
int here_doc(char *delim)
{
	char	*line;
	int		fd[2];
	int		written[2];

	if (!delim || !*delim || pipe(fd) < 0)
		return (-1);
	while (1) 
	{
		line = readline(">");
		if (!line || !ft_strncmp(delim, line, ft_strlen(delim) + 1))
		{
			free(line);
			break;
		}
		written[0] = write(fd[1], line, ft_strlen(line));
		written[1] = write(fd[1], "\n", 1);
		free(line);
		if (written[0] < 0 || written[1] < 0)
			break ;
	}
	close(fd[1]);
	return(fd[0]);
}

int	has_heredoc(t_token	*tok, int segment)
{
	while (tok)
	{
		if (tok->type == HEREDOC)
			return (1);
		if (tok->type == PIPE && segment)
			return (0);
		tok = tok->next;
	}
	return (0);
}

void	free_heredocs(t_here *doc)
{
	if (!doc)
		return ;
	free_heredocs(doc->next);
	free(doc);
}

static t_here	*make_new_heredoc(t_here *head)
{
	t_here	*node;

	node = malloc(sizeof(t_here));
	if (!node)
	{
		free_heredocs(head);
		exit_program(OUT_OF_MEMORY);
	}
	*node = (t_here){0};
	return (node);
}

t_here	*get_heredocs(t_token *tok)
{
	t_here	*start;

	if (!has_heredoc(tok, 0))
		return (NULL);
	start = make_new_heredoc();
	cursor = start;
	while (tok)
	{
		if (tok->type == HEREDOC && tok->next)
		{
			if (cursor->fd)
				close(cursor->fd);
			cursor->fd = here_doc(tok->next->str);
		}
		else if (tok->type == PIPE && has_heredoc(tok, 0))
		{
			cursor->next = make_new_heredoc();
			cursor = cursor->next;
		}
		tok = tok->next;
	}
	return (start);
}
