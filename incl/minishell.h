/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inwagner <inwagner@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:09:26 by inwagner          #+#    #+#             */
/*   Updated: 2023/07/30 14:00:25 by inwagner         ###   ########.fr       */
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
# define ACTIVE 0
# define INACTIVE 1
# define DEFAULT 2

// Structs
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_cli
{
	char			*cmd;
	char			**args;
	char			*director;
	char			*exec;
	struct s_cli	*next;
}					t_cli;

typedef struct s_ctrl
{
	t_cli	*cli;
	t_env	*env;
	char	*exec_path;
	char	*read_line;
	int		last_exit;
}			t_ctrl;

/* STRINGIFY FUNCTIONS */
char	**stringify_envp(t_env *list);
char	**stringify_args(char *args);
int		count_list(t_env *list);
void	copy_key_or_value(t_env *var, char *dst, char *src);
/* PARSE ENV FUNCTIONS */
// Main
t_env	*parse_env(char **env);
void	update_env(char **argv, char *cmd, char *exec);

// Utils
t_env	*add_var(t_env *prev, char *var);
t_env	*search_var(char *str, t_env *list);
t_env	*remove_var(char *str, t_env *list);
char	*get_var_value(char *value, t_env *env_list);
void	set_var(const char *src, t_env *node);
void	clear_command_input(t_cli *cli);
void	clear_ptr_array(char **array);
void	exit_program(int code);
int		special_var_treat(char **copy, int *index);
int		goto_next_quote(char *args);
int		count_args(char *args);
int		size_minus_quotes(char *arg, int len);
/* PARSE INPUT FUNCTIONS */
// Main
t_cli	*parse_input(char *input, char *path);
char	*expand_line(char *line);

// Validators
int		is_builtin(char *cmd);
int		is_exec(char *path, char *cmd);
int		is_redirector(char *red);
int		is_bracket(char c);
int		is_pipe(char c);
int		is_quote(char c);
int		is_a_quoted_var(char *str);
int		bar_input(char *input);
int		quote_closes(char *str);
int		valid_var_name(char c);
char	*var_has_quote(t_env *env_var);
char	*parse_path(char *path, char *cmd);

// Gets
t_ctrl	*get_control(void);
char	*get_cli(char *input, int *i);
char	*get_redirector(char *input, int *i);
char	*get_cmd(char *cli, int *start, int *end, char *path);
char	*get_args(char *cli, int *start, int *end);
int		get_quote(char *input, int *i);

/* BUILTINS */
/* Controller */
void	call_builtin(char *builtin, char **args, t_env *env);

/* Commands */
int		b_cd(char **path, t_env *env);
int		b_echo(char **args);
int		b_env(char **path, t_env *list);
int		b_exit(char **args);
int		b_export(t_env *env, char **args);
int		b_pwd(void);
int		b_unset(t_env *env, char **args);

void	new_var(t_env *env, char *args);
int		export_without_args(t_env *env);
void	ft_quick_sort(char **strings, int low, int high);
int		ft_strcmp(const char *str1, const char *str2);

/* EXECS */
/* Main */
void	call_execve(char *exec, char **args, t_env *env);

/* SIGNALS */
void	set_signals(int mode);

#endif