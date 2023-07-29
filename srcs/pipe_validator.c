/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_validator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 13:15:28 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/29 14:45:46 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_single_brackets(char *input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	while (ft_isblank(input[i]))
		i--;
	if (!is_bracket(input[i]))
		return (0);
	print_error("syntax error near unexpected token `", "newline", 0);
	return (1);
}
