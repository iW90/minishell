/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:08:26 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 11:31:15 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	dup = (char *)ft_calloc(len, sizeof(char));
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, s1, len);
	return (dup);
}
