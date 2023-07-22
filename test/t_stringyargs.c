#include "minishell.h"

static void	print_cmds(void)
{
	t_ctrl	*ctrl = get_control();
	t_cli	*temp;
	char	**args;

	if (ctrl)
		temp = ctrl->cli;
	else
		temp = NULL;
	int	i = 1;
	args = NULL;
	while (temp)
	{
		if (temp && temp->cmd)
			printf("Command %i: %s\n", i, temp->cmd);
		if (temp && temp->args)
			printf("Arg %i: %s\n", i, temp->args);
		if (temp && temp->director)
			printf("Dir %i: %s\n", i, temp->director);
		if (temp && temp->full_exec)
			printf("Exec: %i: %s\n", i, temp->full_exec);
		if (temp->args)
			args = stringify_args(temp->args);
		if (args)
		{
			print_args(args);
			clear_ptr_array(args);
		}
		args = NULL;
		i++;
		temp = temp->next;
		write(1, "\n", 1);
	}
}

static void	print_args(char **args)
{
	int			i;
	static int	argun;

	i = 1;
	argun++;
	while (*args)
		printf("\nPRINTING ARGS\nchar ** number %i\n arg%i: %s\n", argun, i++, *args++);
}

static void	print_args2(char **args)
{
	int	i;

	i = 1;
	while (*args) {
		printf("len is %li ", ft_strlen(*args));
		printf("%i: %s\n\n", i++, *args++);
	}
}

int	main(int argc, char **argv)
{
	char	**ptrs;

	if (argc < 2)
		return (-1);
	ptrs = stringify_args(argv[1]);
	print_args(ptrs);
	clear_ptr_array(ptrs);
}

/*
gcc -Wall -Werror -Wextra -I ./incl ./test/t_stringyargs.c ./srcs/input_stringify.c ./srcs/builtin_env.c ./srcs/builtin_export.c ./srcs/builtin_caller.c ./srcs/cleaner.c ./srcs/env_parser.c ./srcs/env_utils.c ./srcs/exec_finder.c ./srcs/input_parser_gets.c ./srcs/input_parser.c ./srcs/input_utils.c  ./libs/libft/libft.a -o strin
*/



/*
export 'pog="mi'igo"lalalabog'imm"igoooo'heh'                                                   bog=lololo"hey mal'ucao"pogz

*/