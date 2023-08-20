/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:01:44 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/08 14:09:30 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <ctype.h>
#include "libft.h"

void	ft_atoi_tester(void);
void	ft_itoa_tester(void);
void	ft_abs_tester(void);

int		main(void)
{
	//ft_atoi_tester();
	//ft_abs_tester();
	ft_itoa_tester();
	return (0);
}

void	ft_abs_tester(void)
{
	int		i;

	i = -3;
	while (i < 4)
	{
		if (ft_abs(i) == (size_t)abs(i))
			printf("Teste %i\t | ✓ Correct.\n", i);
		else
			printf("Teste %i | ✗ Incorrect.: abs: %i | ft_atbs: %li\n", i, abs(i), ft_abs(i));
		i++;
	}
	printf("Teste %i | ft_abs: %li\n", (int)I_MIN, ft_abs(I_MIN));
	printf("Sizeof %li\n", sizeof(-2147483648));
}

void	ft_itoa_tester(void)
{
	int		size = 13;
	char	str[11];
	char	*ft_str;
	int		num[size];
	int		i;
	
	num[0] = 987;
	num[1] = 12304;
	num[2] = -56708;
	num[3] = 0;
	num[4] =   42 ;
	num[5] = 1000;
	num[6] = 100123;
	num[7] = 456-1;
	num[8] = +10;
	num[9] = +5;
	num[10] = -42;
	num[11] = 2147483647;
	num[12] = -2147483648;
	i = 0;
	while (i < size)
	{
		sprintf(str, "%d", num[i]);
		ft_str = ft_itoa(num[i]);
		printf("Teste %i: % 7d\t | sprintf: %s   \t ft_itoa: %s\n", i, num[i], str, ft_str);
		i++;
	}
}

void	ft_atoi_tester(void)
{
	int		size = 13;
	int		i;
	char	str0[] = "987";
	char	str1[] = "012304";
	char	str2[] = "-56708";
	char	str3[] = "0";
	char	str4[] = "2147483647";
	char	str5[] = "-2147483648";
	char	str6[] = "abc123";
	char	str7[] = "456def";
	char	str8[] = "+";
	char	str9[] = "++5";
	char	str10[] = "--42";
	char	str11[] = "  42 ";
	char	str12[] = "";
	char	*str[size];

	str[0] = str0;
	str[1] = str1;
	str[2] = str2;
	str[3] = str3;
	str[4] = str4;
	str[5] = str5;
	str[6] = str6;
	str[7] = str7;
	str[8] = str8;
	str[9] = str9;
	str[10] = str10;
	str[11] = str11;
	str[12] = str12;

	i = 0;
	while (i < size - 1)
	{
		if (ft_atoi(str[i]) == atoi(str[i]))
			printf("Teste %s\t | ✓ Correct.\n", str[i]);
		else
			printf("Teste %s | ✗ Incorrect.: atoi: %i | ft_atoi: %i\n", str[i], atoi(str[i]), ft_atoi(str[i]));
		i++;
	}
}

// clang -Wall -Werror -Wextra -I ../incl/ ft_isdigit.c ft_isspace.c ft_atoi.c ft_abs.c ft_itoa.c ../test/test_conversion.c