/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:09:26 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/20 14:19:49 by maalexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/incl/libft.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <curses.h>
# include <termios.h>
# include <termcap.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>

# define OUT_OF_MEMORY 1
# define FD_ERROR 2
# define ACTIVE 0
# define INACTIVE 1
# define DEFAULT 2

/*	REDIRECTORS
** |	pipe
** <	input
** <<	heredoc
** >	overwrite
** >>	append
*/
enum e_type
{
	BUILTIN = 1,
	EXEC,
	ARGUMENT
	PIPE,
	HEREDOC,
	APPEND,
	INPUT,
	OVERWRITE,
};

enum e_quote
{
	SINGLE = 1,
	DOUBLE
};

/*	Lists
*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	char			*str;
	enum e_type		type;
	enum e_quote	quote;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/*	Structs
*/
typedef struct s_ctrl
{
	char			*input;
	struct s_token	*tokens;
	struct s_env	*env;
	struct s_cli	*commands;
	char			*path;
	int				status;
}					t_ctrl;

typedef struct s_cli
{
	char			**args;
	int				fd[2];
	enum e_type		type;
	struct s_cli	*next;
}					t_cli;

/*	Functions
*/
void	prompt_user(const char *prompt, t_env *env_list);

void	set_signals(int mode);
void	quick_sort(char **strings, int low, int high);

void	update_env(char **argv, char *cmd, char *exec);
void	set_var(const char *src, t_env *node);
t_env	*parse_env(char **env);
t_env	*remove_var(char *str, t_env *list);
t_env	*search_var(char *str, t_env *list);
t_env	*add_var(t_env *prev, char *var);
char	*get_var_value(char *value, t_env *env_list);
char	**stringify_env(t_env *list);

t_ctrl	*get_control(void);
void	exit_program(int code);
void	clear_tokens(t_token *token);
void	clear_ptr_array(char **array);

char	*parse_path(char *env_path, char *cmd);
void	call_execve(char **args, t_env *env);

int		validate_input(char *input);
int		is_exec(char *path, char *cmd);
int		is_quote(char c);
int		is_bracket(char c);
int		is_pipe(char c);
void	get_quote(char *input, int *i);

int		tokenization(char *input);

#endif