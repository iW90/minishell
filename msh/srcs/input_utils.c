/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:20:34 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/19 13:44:42 by inwagner         ###   ########.fr       */
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
