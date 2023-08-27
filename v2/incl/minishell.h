/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 21:09:26 by inwagner          #+#    #+#             */
/*   Updated: 2023/08/27 15:47:39 by maalexan         ###   ########.fr       */
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


# define OUT_OF_MEMORY 12
# define DEFAULT 0
# define ACTIVE 42
# define INACTIVE 43
# define CMD_NOT_EXECUTABLE 126
# define CMD_NOT_FOUND 127

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

/*	REDIRECTORS
** |	pipe
** <	input
** <<	heredoc
** >	overwrite
** >>	append
*/
typedef enum e_type
{
	APPEND = 1,
	HEREDOC,
	OVERWRITE,
	INPUT,
	PIPE,
	BUILTIN,
	EXEC,
	ARGUMENT
}	t_type;

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
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

/*	Structs
*/
typedef struct s_cli
{
	char			**args;
	int				fd[2];
	enum e_type		type;
	struct s_cli	*next;
}					t_cli;

typedef struct s_ctrl
{
	char			*input;
	t_token			*tokens;
	t_env			*env;
	t_cli			*commands;
	char			**pbox;
	int				status;
}					t_ctrl;


typedef struct s_here
{
	int				fd;
	struct s_here	*next;
}					t_here;

/*	Functions
*/
void	prompt_user(const char *prompt);

void	set_signals(int mode);
void	quick_sort(char **strings, int low, int high);

void	update_env(char **argv, char *cmd, char *exec);
void	set_var(const char *src, t_env *node);
t_env	*parse_env(char **env);
t_env	*remove_var(char *str, t_env *list);
t_env	*search_var(char *var);
t_env	*add_var(t_env *prev, char *var);
char	*get_var_value(char *value);
char	**stringify_env(t_env *list);

t_ctrl	*get_control(void);
void	exit_program(int code);
void	clear_tokens(t_token *token);
void	clear_pbox(char **array);

char	*get_exec_path(char *env_path, char *cmd);
void	call_execve(char **args, t_env *env);

int		validate_input(char *input);
int		is_bracket(char c);
int		is_pipe(char c);
void	get_quote(char *input, int *i);

int		is_var(char var);
int		is_builtin(char *cmd);
int		is_redirector(char *red);
int		is_quote(char quote);

int		tokenization(char *input);
int		parser(void);

int		has_var(char *str);
void	free_pbox(char **pbox, int size);
void	null_pbox(char **pbox, int size);
char	*copy_str(char *input, int start, int len);
void	link_token(t_token *current, t_token *last);

char	*set_pipe_token(char *input, int *i, t_token *token);
char	*set_redirector_token(char *input, int *i, t_token *token);
char	*set_str_token(char *input, int *i);

char	*set_quoted_token(char *input, int *i);
char	*set_expanded_token(char *input, int *i);

char	*expand_token(char **str, int *j);
char	*get_var(char *var, int *i);

void	call_builtin(t_cli *cli);
int		b_cd(char **path);
int		b_echo(char **args);
int		b_env(char **path, t_env *list);
int		b_exit(char **args);
int		b_export(t_env *env, char **args);
int		b_pwd(void);
int		b_unset(char **args, t_env *env);

int		export_without_args(t_env *env);



void	assemble_tokens(t_token *tok_nav);

void	remove_token(t_token *node);
int		count_args(t_token *node);
int		count_nodes(t_token *tok);
int		has_heredoc(t_token	*tok);

t_cli	*make_new_cli(t_here *head);

t_here	*get_heredocs(t_token *tok);
void    free_heredocs(t_here *doc, char closing);
void	assemble_fds(t_cli *cli, t_token *tok, t_here *heredocs);

//remove
void print_cli(void);
void	print_token(t_token *tokens);

#endif