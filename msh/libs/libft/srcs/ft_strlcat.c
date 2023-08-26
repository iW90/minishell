/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:09:35 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 18:12:53 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	dlen;

	dlen = ft_strlen(dst);
	if (len <= dlen)
		return (len + ft_strlen(src));
	i = -1;
	while (dlen + i != len - 1 && src[++i])
		dst[dlen + i] = src[i];
	dst[dlen + i] = 0;
	return (dlen + ft_strlen(src));
}
