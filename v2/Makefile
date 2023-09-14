# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 11:13:39 by maalexan          #+#    #+#              #
#    Updated: 2023/09/13 22:14:11 by maalexan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME		:=	minishell

# Directories for source, object and libraries
SRC_DIR		:=	./srcs
OBJ_DIR		:=	./objs
BSRC_DIR	:=	./bonus/srcs
HDR_DIR		:=	./incl
FTLIB_DIR	:=	./libs/libft
FTLIB		:=	$(FTLIB_DIR)/libft.a

# Compilation flags
CFLAGS		:=	-Wall -Wextra -Werror -g -I $(HDR_DIR)
BCFLAGS		:=	-Wall -Wextra -Werror -g -I ./bonus/incl

# Source files
FUN			:=	main.c \
				builtin_caller.c \
				builtin_cd.c \
				builtin_echo.c \
				builtin_env.c \
				builtin_exit.c \
				builtin_export_print.c \
				builtin_export.c \
				builtin_pwd.c \
				builtin_unset.c \
				cleaner.c \
				env_parser.c \
				env_shifter.c \
				env_utils.c \
				exec_finder.c \
				exec_run.c \
				executor_cli.c \
				executor_constructor.c \
				executor_fd.c \
				executor_fork.c \
				executor_heredoc.c \
				executor_list.c \
				executor.c \
				input_utils.c \
				input_validator.c \
				parser.c \
				prompt.c \
				quick_sort.c \
				signal_handler.c \
				token_expander_var.c \
				token_expander.c \
				token_helpers.c \
				token_list.c \
				token_populator.c \
				token_string_handler.c \
				token_utils.c \
				tokenization.c

# Object files
OBJ			:=	$(FUN:%.c=$(OBJ_DIR)/%.o)
BOBJ		:=	$(BFUN:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ) $(FTLIB)
	cc $(OBJ) $(FTLIB) -lreadline -o $@

$(FTLIB):
	@$(MAKE) -C $(FTLIB_DIR) --silent

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	cc $(CFLAGS) -c $< -o $@

bonus: $(NAMEB)

$(NAMEB): $(BOBJ) $(FTLIB)
	cc $(BOBJ) $(FTLIB) -o $@

$(OBJ_DIR)/%.o: $(BSRC_DIR)/%.c
	@mkdir -p $(@D)
	@cc $(BCFLAGS) -c $< -o $@

val: all
	@valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./${NAME} || echo ""

supp:
	@printf "{\n        <Readline>\n        Memcheck:Leak\n        match-leak-kinds: reachable\n        ...\n        fun:readline\n        ...\n}\n{\n        <Readline>\n        Memcheck:Leak\n        match-leak-kinds: definite\n        fun:malloc\n        fun:xmalloc\n        fun:rl_add_undo\n        fun:rl_insert_text\n        fun:_rl_insert_char\n        fun:rl_insert\n        fun:_rl_dispatch_subseq\n        fun:readline_internal_char\n        fun:readline\n        ...\n}\n{\n        <AddHistory>\n        Memcheck:Leak\n        match-leak-kinds: reachable\n        fun:malloc\n        fun:xmalloc\n        fun:add_history\n        ...\n}\n" > readline.supp

clean:
	@$(MAKE) -C $(FTLIB_DIR) --silent clean
	@[ -d ./objs ] && rm -rf ./objs || echo Object directory doesn\'t exist

fclean: clean
	@$(MAKE) -C $(FTLIB_DIR) --silent fclean
	@[ -f ./$(NAME) ] && rm $(NAME) || echo Program $(NAME) isn\'t compiled
	@[ -f ./$(NAMEB) ] && rm $(NAMEB)|| echo Bonus $(NAMEB) isn\'t compiled

re: fclean all

.PHONY: all bonus clean fclean re