/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_strtok.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:43:42 by inwagner          #+#    #+#             */
/*   Updated: 2023/06/09 13:29:59 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

void test_ft_strtok(const char *str, const char *delimiters)
{
	char	str_copy[100];
	char	str_copy2[100];
	char	*token;
	char	*token2;
	
	strcpy(str_copy, str);  // Fazer uma cópia da string original para preservá-la
	strcpy(str_copy2, str_copy);  // Fazer uma segunda cópia para o teste usando strtok original

	printf("String: %s\n", str_copy);
	printf("Delimiters: %s\n", delimiters);

	token = ft_strtok(str_copy, delimiters);
	token2 = strtok(str_copy2, delimiters);

	while (token != NULL && token2 != NULL) {
		printf("ft_token: %s    \t|\ttoken: %s\n", token, token2);
		token = ft_strtok(NULL, delimiters);
		token2 = strtok(NULL, delimiters);
	}

	printf("--------------------\n");
}

int main()
{
	test_ft_strtok("Hello, World!", " ,");  // Esperado: Hello | World!
	test_ft_strtok("Lorem ipsum dolor sit amet", " ");  // Esperado: Lorem | ipsum | dolor | sit | amet
	test_ft_strtok("abc,def,ghi,jkl", ",");  // Esperado: abc | def | ghi | jkl
	test_ft_strtok("one;two;three;four", ";");  // Esperado: one | two | three | four
	test_ft_strtok("apple,banana,,grape", ",");  // Esperado: apple | banana | (vazio) | grape
	test_ft_strtok("The_quick_brown_fox", "_");  // Esperado: The | quick | brown | fox
	test_ft_strtok(" ", ".");  // Esperado: (espaço)
	test_ft_strtok("Testando..test1.test2, teste3", ".,");  // Esperado: Testando | test1 |  test3 (delimitador é um charset)
	test_ft_strtok("|Bugbug~byebye|", "|");  // Esperado: Bugbug~byebye
	test_ft_strtok("", "i");  // Esperado:

	return 0;
}

//clang -Wall -Werror -Wextra -I ../incl/ ft_strtok.c ft_strcspn.c ft_strspn.c ft_strchr.c ft_strlen.c ../test/tester_strtok.c
