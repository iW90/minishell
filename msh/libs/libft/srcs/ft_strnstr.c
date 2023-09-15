/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:08:30 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 11:32:28 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	littlen;

	if (!*little)
		return ((char *)big);
	littlen = ft_strlen(little);
	while (*big && littlen <= n--)
	{
		if (!ft_strncmp(big, little, littlen))
			return ((char *)big);
		big++;
	}
	return (0);
}
