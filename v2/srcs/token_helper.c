/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 22:34:31 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/26 19:09:28 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_var(char *str)
{
	while (*str)
	{
		if (*str == '$' && is_var(*(str + 1)))
			return (1);
		str++;
	}
	return (0);
}

void	free_pbox(char **pbox, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		if (pbox[i])
			free(pbox[i]);
	null_pbox(pbox, size);
}

void	null_pbox(char **pbox, int size)
{
	int		i;

	i = -1;
	while (++i < size)
			pbox[i] = NULL;
}

char	*copy_str(char *input, int start, int len)
{
	char	*str;

	str = malloc(sizeof(char) * len);
	if (!str)
		exit_program(OUT_OF_MEMORY);
	ft_strlcpy(str, &input[start], len);
	return (str);
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
