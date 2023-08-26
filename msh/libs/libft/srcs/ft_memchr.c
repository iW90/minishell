/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:07:30 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 11:24:04 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	chr;

	str = (unsigned char *)src;
	chr = (unsigned char)c;
	i = -1;
	while (++i < n)
		if (str[i] == chr)
			return ((void *)&str[i]);
	return (0);
}
