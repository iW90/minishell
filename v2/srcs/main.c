/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:37:15 by inwagner          #+#    #+#             */
/*   Updated: 2023/09/13 09:59:58 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ctrl	*get_control(void)
{
	static t_ctrl	control;

	return (&control);
}

int	main(int argc, char **argv, char **env)
{
	t_ctrl	*control;

	(void)argc;
	control = get_control();
	control->env = parse_env(env);
	update_env(argv, NULL, NULL);
	while (1)
		prompt_user("msh:> ");
	exit_program(0);
}

/*
Test 100: ❌ echo hi | >./outfiles/outfile01 echo bye >./test_files/invalid_permission 
Only in ./bash_outfiles: outfile01
mini outfiles:
cat: './mini_outfiles/ *': No such file or directory
bash outfiles:
mini exit code = 0
bash exit code = 1
mini error = ( syntax error near unexpected token `>')
bash error = ( Permission denied)

Test 134: ❌ $EMPTY 
mini exit code = 127
bash exit code = 0
mini error = ( command not found)
bash error = ()

Test 135: ❌ $EMPTY echo hi 
mini output = ()
bash output = (hi)
mini exit code = 127
bash exit code = 0
mini error = ( command not found)
bash error = ()
*/