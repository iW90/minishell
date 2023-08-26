/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:08:39 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 18:11:08 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	ls1;
	size_t	ls2;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	str = (char *)ft_calloc(ls1 + ls2 + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_memmove(str, s1, ls1);
	ft_strlcat(str, s2, ls1 + ls2 + 1);
	return (str);
}
