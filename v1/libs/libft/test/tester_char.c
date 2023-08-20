/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:43:42 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/08 12:55:21 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include "libft.h"

void	ft_is_tester(int (*f)(int), int (*ft_f)(int), int test);
int		ft_to_tester(int (*f)(int), int (*ft_f)(int), int test);

int main(void)
{
	int		i;
	//char	str[] = "Life is like a CAMERA. Focus on the GOOD TIMES, develop from the negatives, and if things do not work out, TAKE ANOTHER SHOT.\n";

	/* IS TESTER
	i = 0;
	while (i < 128)
	{
		//ft_is_tester(&isalnum, &ft_isalnum, i);
		//ft_is_tester(&isalpha, &ft_isalpha, i);
		//ft_is_tester(&isascii, &ft_isascii, i);
		//ft_is_tester(&isdigit, &ft_isdigit, i);
		//ft_is_tester(&isprint, &ft_isprint, i);
		//ft_is_tester(&isspace, &ft_isspace, i);
		//ft_is_tester(&isupper, &ft_isupper, i);
		//ft_is_tester(&islower, &ft_islower, i);
		//ft_is_tester(&isblank, &ft_isblank, i);
		//ft_is_tester(&isgraph, &ft_isgraph, i);
		//ft_is_tester(&ispunct, &ft_ispunct, i);
		//ft_is_tester(&isxdigit, &ft_isxdigit, i);
		i++;
	}
	*/
	
	/* TO LOWER TESTER
	i = 0;
	while (ft_to_tester(&tolower, &ft_tolower, str[i]))
		i++;
	*/
		
	/* TO LOWER TESTER
	i = 0;
	while (ft_to_tester(&toupper, &ft_toupper, str[i]))
		i++;
	*/
	
	return (0);
}

void	ft_is_tester(int (*f)(int), int (*ft_f)(int), int test)
{
	int c;
	int	ft_c;

	c = f(test);
	ft_c = ft_f(test);
	if ((c && ft_c) || (!c && !ft_c))
		printf("ASCII %03i | ✓ Correct.\n", test);
	else
		printf("ASCII %03i | ✗ Incorrect.\n", test);
}

int		ft_to_tester(int (*f)(int), int (*ft_f)(int), int test)
{
	int c;
	int	ft_c;

	c = f(test);
	ft_c = ft_f(test);
	if (c == ft_c)
		printf("%c", ft_f(test));
	else
		return (0);
	return (1);
}

// clang -Wall -Werror -Wextra -I ../incl/ ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c tester_char.c ft_tolower.c ft_toupper.c ft_isblank.c ft_isgraph.c ft_islower.c ft_isupper.c ft_isxdigit.c ft_ispunct.c