/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:10:28 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 13:03:37 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delimiters)
{
	static char	*ptr;

	if (!str)
	{
		str = ptr;
		if (!str)
			return (NULL);
	}
	str += ft_strspn(str, delimiters);
	if (!*str)
		return (ptr = 0);
	ptr = str + ft_strcspn(str, delimiters);
	if (*ptr)
		*ptr++ = 0;
	else
		ptr = 0;
	return (str);
}
