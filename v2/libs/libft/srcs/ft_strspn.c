/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:06:56 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 12:28:43 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *str, const char *charset)
{
	size_t	count;

	count = 0;
	while (*str)
	{
		if (ft_strchr(charset, *str))
			count++;
		else
			break ;
		str++;
	}
	return (count);
}
