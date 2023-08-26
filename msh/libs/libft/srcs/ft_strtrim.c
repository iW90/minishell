/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:09:02 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 11:32:04 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1 || !set)
		return (0);
	size = ft_strlen(s1);
	i = 0;
	j = size - 1;
	while (ft_strchr(set, s1[i]) && s1[i++])
		size--;
	while (j > i && ft_strchr(set, s1[j--]))
		size--;
	return (ft_substr(s1, i, size));
}
