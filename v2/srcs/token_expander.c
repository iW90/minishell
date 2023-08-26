/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 10:13:36 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/20 16:46:56 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_str(char **pbox, char *str)
{
	char	*expanded;

	if ((pbox[2] && pbox[2][0]) && str[0])
	{
		expanded = ft_strjoin(pbox[2], str);
		if (!expanded)
			exit_program(OUT_OF_MEMORY);
	}
	else if (!(pbox[2] && pbox[2][0]) && str[0])
	{
		expanded = ft_strdup(str);
		if (!expanded)
			exit_program(OUT_OF_MEMORY);
	}
	else if ((pbox[2] && pbox[2][0]) && !str[0])
	{
		expanded = ft_strdup(pbox[2]);
		if (!expanded)
			exit_program(OUT_OF_MEMORY);
	}
	else
		return (NULL);
	return (expanded);
}

static char	*join_strs(char **pbox, char *str)
{
	if ((pbox[0] && pbox[0][0]) && (pbox[1] && pbox[1][0]))
	{
		pbox[2] = ft_strjoin(pbox[0], pbox[1]);
		if (!pbox[2])
			exit_program(OUT_OF_MEMORY);
	}
	else if ((pbox[0] && pbox[0][0]) && !(pbox[1] && pbox[1][0]))
	{
		pbox[2] = ft_strdup(pbox[0]);
		if (!pbox[2])
			exit_program(OUT_OF_MEMORY);
	}
	else if (!(pbox[0] && pbox[0][0]) && (pbox[1] && pbox[1][0]))
	{
		pbox[2] = ft_strdup(pbox[1]);
		if (!pbox[2])
			exit_program(OUT_OF_MEMORY);
	}
	return (join_str(pbox, str));
}

char	*expand_token(char **str)
{
	int		i;
	int		start;
	int		len;
	char	*expanded;

	i = -1;
	start = 0;
	while (str[3][++i])
		if (str[3][i] == '$' && is_var(str[3][i + 1]))
			break ;
	len = ++i - start;
	if (len > 1)
		str[0] = copy_str(str[3], start, len);
	str[1] = get_var(str[3], &i);
	expanded = join_strs(str, &str[3][i]);
	free_pbox(str, 4);
	if (!expanded)
		return (ft_calloc(1, sizeof(char)));
	return (expanded);
}
