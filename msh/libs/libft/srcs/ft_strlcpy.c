/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:09:49 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 17:37:28 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	if (!len)
		return (ft_strlen(src));
	i = -1;
	while (src[++i] && i < len - 1)
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}
