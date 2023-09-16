/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:56:32 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/16 13:46:42 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap(char **str1, char **str2)
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

void	quick_sort(char **strings, int low, int high)
{
	int	pivot;

	if (low < high)
	{
		pivot = partition(strings, low, high);
		quick_sort(strings, low, pivot - 1);
		quick_sort(strings, pivot + 1, high);
	}
}
