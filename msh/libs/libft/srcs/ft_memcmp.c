/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:08:38 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 11:24:14 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *stra, const void *strb, size_t n)
{
	size_t			i;
	unsigned char	*cstra;
	unsigned char	*cstrb;

	cstra = (unsigned char *)stra;
	cstrb = (unsigned char *)strb;
	i = -1;
	while (++i < n)
		if (cstra[i] != cstrb[i])
			return ((int)(cstra[i] - cstrb[i]));
	return (0);
}
