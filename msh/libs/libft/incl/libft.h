/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:03:22 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/08 11:59:11 by inwagner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef I_MAX
#  define I_MAX 2147483647
# endif

# ifndef I_MIN
#  define I_MIN -2147483648
# endif

// Char
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_isspace(int c);
int		ft_isblank(int c);
int		ft_isgraph(int c);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_ispunct(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isxdigit(int c);

// String
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *src, int c);
char	*ft_strnstr(const char *big, const char *little, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strrchr(const char *src, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlcat(char *dst, const char *src, size_t len);
size_t	ft_strlcpy(char *dst, const char *src, size_t len);
size_t	ft_strlen(const char *src);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_strncmp(const char *str1, const char *str2, size_t n);
int		ft_strcmp(const char *str1, const char *str2);

// Conversion
size_t	ft_abs(int n);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);

// Memory
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t num, size_t size);
void	*ft_memchr(const void *src, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	*ft_memset(void *src, int c, size_t n);
int		ft_memcmp(const void *stra, const void *strb, size_t n);

// File Descriptor
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);

// New Functions
size_t	ft_strspn(const char *str, const char *charset);
size_t	ft_strcspn(const char *str, const char *reject);
char	*ft_strtok(char *str, const char *delimiters);

#endif