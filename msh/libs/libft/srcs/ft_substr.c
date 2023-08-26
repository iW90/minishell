/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:09:16 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 11:32:08 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (start > slen || !len)
		return (ft_strdup(""));
	if (slen - start < len)
		len = slen - start;
	sub = (char *)ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (0);
	ft_memcpy(sub, &s[start], len);
	return (sub);
}
