/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:20:34 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/20 22:40:21 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	PEGA O TRECHO ENTRE QUOTES
** Enquanto a quote estiver aberta, o restante do código
** não será interpretado, considerando como parte do
** conteúdo quotado.
** Sai do programa se não fechar o quote.
*/
void	get_quote(char *input, int *i)
{
	char	quote;

	quote = input[(*i)++];
	while (input[*i] && input[*i] != quote)
		(*i)++;
}

int	is_bracket(char c)
{
	return (c == '>' || c == '<');
}

int	is_pipe(char c)
{
	return (c == '|');
}
