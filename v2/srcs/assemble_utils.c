/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:49:48 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/23 22:25:16 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_token *node)
{
	int	count;

	count = 0;
	while (node && node->type == ARGUMENT)
	{
		node = node->next;
		count++;
	}
	return (count);
}

void	remove_token(t_token *node)
{
	t_token	*prev;
	t_token	*next;

	if (!node)
		return ;
	prev = node->prev;
	next = node->next;
	if (node->str)
		free(node->str);
	free(node);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (!prev && !next)
		get_control()->tokens = NULL;
}

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

/*
**	Makes sure the t_cli node has it's input and
**	output file descriptor properly set
*/
int	prepare_fd(t_token *node, int *fd)
{
	char	*file;
	t_token	*next;

	if (!node || !node->next || !node->next->str)
		return (-1);
	next = node->next;
	file = next->str;
	if (node->type == HEREDOC)
		fd[0] = here_doc(file);
	else if (node->type == INPUT)
		fd[0] = open(file, O_RDONLY);
	else if (node->type == APPEND)
		fd[1] = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
	else if (node->type == OVERWRITE)
		fd[1] = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	remove_token(next);
	remove_token(node);
	if (fd[0] == -1 || fd[1] == -1)
		return (-1);
	return (0);
}

 /*
token tok1						token tok2					token tok3						token tok4						token tok5
{								{							{								{								{
	tok1->str = "cat";				tok2->str = "file";			tok3->str = ">>";				tok4->str = "outputted";		tok5->str = "|";
	tok1->type = EXEC;				tok2->type = ARG;			tok3->type = APPEND;			tok4->type = ARG;				tok5->type = PIPE;
	tok1->prev = NULL;				tok2->prev = tok1;			tok3->prev = tok2;				tok4->prev = tok3;				tok5->prev = tok4;
	tok1->next = tok2;				tok2->next = tok3;			tok3->next = tok4;				tok4->next = tok5;				tok5->next = tok6;
}								}							}								}								}


token tok6						token tok7					token tok8						token tok9					
{								{							{								{							
	tok6->str = "grep";				tok7->str = "example";		tok8->str = "<";				tok9->str = "f.txt";	
	tok6->type = EXEC;				tok7->type = ARG;			tok8->type = INPUT;				tok9->type = ARG;		
	tok6->prev = tok5;				tok7->prev = tok6;			tok8->prev = tok7;				tok9->prev = tok8;		
	tok6->next = tok7;				tok2->next = tok8;			tok8->next = tok9;				tok9->next = NULL;		
}								}							}								}			
*/