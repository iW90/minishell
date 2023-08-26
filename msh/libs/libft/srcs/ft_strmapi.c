/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 19:08:51 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 11:31:47 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*str;

	len = ft_strlen(s) + 1;
	str = (char *)ft_calloc(len, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (s[++i])
		str[i] = f(i, s[i]);
	return (str);
}
