/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 20:49:48 by maalexan          #+#    #+#             */
/*   Updated: 2023/08/20 14:33:51 by maalexan         ###   ########.fr       */
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
**	Takes the end of a list and pipe it
**	so each fd is ready to be dupped on
**	executing the commands
*/

t_cli	set_pipe(t_cli *prev)
{
	t_cli	*node;

	node = malloc(sizeof(t_cli));
	if (!node)
		exit_program(OUT_OF_MEMORY);
	*node = (t_cli){0};
	prev->next = node;
	node->type = PIPE;
	pipe(prev->fd);
	return (node);
}
