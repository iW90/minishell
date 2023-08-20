/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 19:51:12 by maalexan          #+#    #+#             */
/*   Updated: 2023/07/18 18:10:25 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	copy_i_to_str(int num, char *str, int len)
{
	if (!num)
		*str = '0';
	else
	{
		while (num)
		{
			str[--len] = (num % 10) + '0';
			num /= 10;
		}
	}
}

int	special_var_treat(char **copy, int *index)
{
	t_ctrl	*ctrl;
	int		size;
	int		temp;

	size = 0;
	ctrl = get_control();
	temp = (unsigned char)ctrl->last_exit;
	(*index)++;
	if (!temp)
		temp = 1;
	while (temp)
	{
		temp /= 10;
		size++;
	}
	if (copy)
		copy_i_to_str((unsigned char)ctrl->last_exit, *copy, size);
	return (size);
}
