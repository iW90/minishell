/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:56:32 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/28 22:53:34 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* QUICK SORT:
 * Ordenador que utiliza o conceito "dividir para conquistar".
 * É definido um pivô que servirá como divisória para colocar
 * números menores do lado esquerdo e números maiores do direito.
 * Cada parte será dividida em duas recursivamente, delimitada pelo 
 * pivô, sempre definindo um novo pivô para cada partição até que
 * a pilha fique ordenada.
 * O pivô utilizado neste quick sort é o último elemento do array,
 * e no final ele é colocado na divisória entre menores e maiores
 * para servir de referência para a próxima partição.
 * O número comparado é a diferença entre os caracteres de cada
 * string, considerando seu valor na tabela ASCII.
 */
int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

void	ft_swap(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

static int	partition(char **strings, int low, int high)
{
	char	*pivot;
	int		i;
	int		j;

	pivot = strings[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (ft_strcmp(strings[j], pivot) <= 0)
			ft_swap(&strings[++i], &strings[j]);
		j++;
	}
	ft_swap(&strings[i + 1], &strings[high]);
	return (i + 1);
}

void	ft_quick_sort(char **strings, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition(strings, low, high);
		ft_quick_sort(strings, low, pivot - 1);
		ft_quick_sort(strings, pivot + 1, high);
	}
}
