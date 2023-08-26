/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcspn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:11:45 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 17:13:37 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcspn(const char *str, const char *reject)
{
	size_t	size;

	size = 0;
	while (*str)
	{
		if (!ft_strchr(reject, *str))
			size++;
		else
			break ;
		str++;
	}
	return (size);
}
