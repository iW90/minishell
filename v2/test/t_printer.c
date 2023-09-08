#include "minishell.h"

static char	*print_type(int type)
{
	if (type == PIPE)
		return ("pipe");
	else if (type == HEREDOC)
		return ("heredoc");
	else if (type == APPEND)
		return ("append");
	else if (type == INPUT)
		return ("input");
	else if (type == OVERWRITE)
		return ("overwrite");
	else if (type == BUILTIN)
		return ("builtin");
	else if (type == EXEC)
		return ("exec");
	else if (type == ARGUMENT)
		return ("arg");
	else
		return ("");
}

void	print_token(t_token *tokens)
{
	static int	count;

	if (!tokens)
	{
		printf("no tokens here\n");
		count = 0;
		return ;
	}
	printf("I'm at token %i str: %s | type: %s\n", count++, tokens->str, print_type(tokens->type));
	print_token(tokens->next);
}

static void	print_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
	{
		printf("No args\n");
		return ;
	}
	while(*args)
		printf("arg[%i] %s / ", i++, *args++);
	printf("EOA\n");
}

void print_cli(void)
{
	t_cli	*current;
	int		i;

	i = 1;
	current = get_control()->commands;
	while (current)
	{
		printf("\nCli number %i\n", i++);
		if (current->args)
			print_args(current->args);
		printf("fd0 is %i and fd1 is %i\n", current->fd[0], current->fd[1]);
		printf("type %s\n", print_type(current->type));
		current = current->next;
	}
}



/*
Model tokens

token tok1						token tok2					token tok3						token tok4						token tok5
{								{							{								{								{
	tok1->str = "cat";				tok2->str = "file";			tok3->str = ">>";				tok4->str = "outputted";		tok5->str = "|";
	tok1->type = EXEC;				tok2->type = ARG;			tok3->type = APPEND;			tok4->type = ARG;				tok5->type = PIPE;
	tok1->prev = NULL;				tok2->prev = tok1;			tok3->prev = tok2;				tok4->prev = tok3;				tok5->prev = tok4;
	tok1->next = tok2;				tok2->next = tok3;			tok3->next = tok4;				tok4->next = tok5;				tok5->next = tok6;
}								}							}								}								}


token tok6						token tok7					token tok8						token tok9					
{								{							{								{							
	tok6->str = "grep";				tok7->str = "example";		tok8->str = "<";				tok9->str = "f.txt";	
	tok6->type = EXEC;				tok7->type = ARG;			tok8->type = INPUT;				tok9->type = ARG;		
	tok6->prev = tok5;				tok7->prev = tok6;			tok8->prev = tok7;				tok9->prev = tok8;		
	tok6->next = tok7;				tok2->next = tok8;			tok8->next = tok9;				tok9->next = NULL;		
}								}							}								}							



fd[0] fd[1]


cli1								cli2								cli3									
{									{									{										
	cli1->args[0] = "cat";				cli->args = NULL;					cli->args[0] = "grep";				
	cli1->args[1] = "file";				cli->type = PIPE;					cli->args[1] = "example";
	cli1->args[2] = NULL;				cli->fd[0] = pipedRead;				cli->type = EXEC;
	cli1->type = EXEC;					cli->fd[1] = pipedWrite;			cli->fd[0] = copyFromCli2;//overwritten by tok8-9
	cli1->fd[0] = 0;					cli->next = cli3;					cli->fd[1] = 0;
	cli1->fd[1] = duped(tok3-4);											cli->next = NULL;
	cli->next = cli2;
}									}									}


*/


/*
void	get_fd(t_token *tok, int *fd, int *has_heredoc)
{
	if (fd[0] && (tok->type == INPUT) && !*has_heredoc)
	{
		close(fd[0]);
		fd[0] = 0;
	}
	if (fd[1] && (tok->type == APPEND || tok->type == OVERWRITE))
	{
		close(fd[1]);
		fd[1] = 0;
	}
	if (tok->type == HEREDOC && last_heredoc())
	if (prepare_fd(tok, fd) < 0)
		exit_program(FD_ERROR);
}

void	file_descriptors(t_token *tok, t_cli *cli)
{
	int	has_heredoc;

	has_heredoc = cli->fd[0];
	while (tok)
	{
		if (tok->type < PIPE)
		{
			tok = tok->prev;
			get_fd(tok->next, cli->fd, &has_heredoc);
		}
		else if (tok->type == PIPE)
		{
			while (cli->type != PIPE)
				cli = cli->next;
			cli = cli->next;
		}
		tok = tok->next;
	}
}

void	heredocs_and_pipes(t_token *tok, t_cli *cli)
{
	while (tok)
	{
		if (tok->type == PIPE)
		{
			cli->next = make_new_node();
			cli = cli->next;
			cli->type = PIPE;
			cli->next = make_new_node();
			cli = cli->next;
			tok = tok->next;
		}
		else if (tok->type == HEREDOC)
		{
			if (cli->fd[0])
				close(cli->fd[0]);
			cli->fd[0] = here_doc(tok->next->str);
		}
		else
			while (tok && tok->type != PIPE && tok->type != HEREDOC)
				tok = tok->next;
	}
}

void	executor_constructor(t_token *tok)
{
	t_cli	*cli;
	t_here	*heredocs;

	if (!tok)
		return ;
	cli = make_new_node();
	get_control()->commands = cli;
	heredocs = get_heredocs(tok);
	// If !heredocs && last->exit = ?? aborta tudo
	
	while (1)
	{
//		print_token(tok);
		cli->type = tok->type;
		if (tok->type > PIPE)
			cli->args = get_cli(tok);
		else if (tok->type < PIPE)
			get_fd(tok, cli->fd);
		else
			pipe_fd(tok, cli->fd);
		tok = get_control()->tokens;
		if (!tok)
			break ;
		else if (tok->type >= PIPE)
		{
			cli->next = make_new_node();
			cli = cli->next;
		}
	}
	print_cli();
}

echo pog >> cato | lala fff grep > bingo | pwd < cato

*/

/*
static char	*print_type_tok(t_token *tokens)
{
	if (!tokens)
		return ("");
	if (tokens->type == PIPE)
		return ("pipe");
	else if (tokens->type == HEREDOC)
		return ("heredoc");
	else if (tokens->type == APPEND)
		return ("append");
	else if (tokens->type == INPUT)
		return ("input");
	else if (tokens->type == OVERWRITE)
		return ("overwrite");
	else if (tokens->type == BUILTIN)
		return ("builtin");
	else if (tokens->type == EXEC)
		return ("exec");
	else if (tokens->type == ARGUMENT)
		return ("arg");
	else
		return ("");
}

void	print_tokens(t_token *tokens)
{
	if (!tokens)
		return ;
	printf("str: %s | type: %s\n", tokens->str, print_type_tok(tokens));
	print_tokens(tokens->next);
}

static char	*print_type(int type)
{
	if (type == PIPE)
		return ("pipe");
	else if (type == HEREDOC)
		return ("heredoc");
	else if (type == APPEND)
		return ("append");
	else if (type == INPUT)
		return ("input");
	else if (type == OVERWRITE)
		return ("overwrite");
	else if (type == BUILTIN)
		return ("builtin");
	else if (type == EXEC)
		return ("exec");
	else if (type == ARGUMENT)
		return ("arg");
	else
		return ("");
}

void	print_token(t_token *tokens)
{
	static int	count;

	if (!tokens)
	{
		count = 0;
		return ;
	}
	printf("I'm at token %i str: %s | type: %s\n", count++, tokens->str, print_type(tokens->type));
	print_token(tokens->next);
}

static void	print_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
	{
		printf("No args\n");
		return ;
	}
	while(*args)
		printf("arg[%i] %s / ", i++, *args++);
	printf("NULL\n");
}

void print_cli(void)
{
	t_cli	*current;
	int		i;

	i = 1;
	current = get_control()->commands;
	while (current)
	{
		printf("\nCli number %i\n", i++);
		if (current->args)
			print_args(current->args);
		printf("fd0 is %i and fd1 is %i\n", current->fd[0], current->fd[1]);
		printf("type %s\n", print_type(current->type));
		current = current->next;
	}
}

/*
static char	*print_type(t_token *tokens)
{
	if (tokens->type == PIPE)
		return ("pipe");
	else if (tokens->type == HEREDOC)
		return ("heredoc");
	else if (tokens->type == APPEND)
		return ("append");
	else if (tokens->type == INPUT)
		return ("input");
	else if (tokens->type == OVERWRITE)
		return ("overwrite");
	else if (tokens->type == BUILTIN)
		return ("builtin");
	else if (tokens->type == EXEC)
		return ("exec");
	else if (tokens->type == ARGUMENT)
		return ("arg");
	else
		return ("");
}

static void	print_tokens(t_token *tokens)
{
	if (!tokens)
		return ;
	printf("str: %s | type: %s\n", tokens->str, print_type(tokens));
	print_tokens(tokens->next);
}
*/
