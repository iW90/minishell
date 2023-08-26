/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:07:11 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 11:28:50 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*dst;
	size_t	sz;

	sz = num * size;
	if (!num || !size || sz / size != num)
		return (NULL);
	dst = malloc(sz);
	if (!dst)
		return (NULL);
	ft_bzero(dst, sz);
	return (dst);
}
