/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:09:24 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 11:32:00 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	long int	i;

	if (!c)
		return ((char *)&src[(long int)ft_strlen(src)]);
	i = ft_strlen(src);
	while (i && src[i] != (char)(c))
		i--;
	if (src[i] == (char)(c))
		return ((char *)&src[i]);
	return (0);
}
