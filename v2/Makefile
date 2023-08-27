# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maalexan <maalexan@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/22 11:13:39 by maalexan          #+#    #+#              #
#    Updated: 2023/08/27 11:30:11 by maalexan         ###   ########.fr        #
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
				assemble_tokens.c \
				assemble_heredoc.c \
				assemble_fds.c \
				assemble_utils.c \
				cleaner.c \
				env_parser.c \
				env_shifter.c \
				env_utils.c \
				exec_finder.c \
				exec_run.c \
				input_utils.c \
				input_validator.c \
				parser.c \
				prompt.c \
				quick_sort.c \
				signal_handler.c \
				token_exp_var.c \
				token_expander.c \
				token_helper.c \
				token_list.c \
				token_setter.c \
				token_str.c \
				token_utils.c \
				token.c 

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

clean:
	@$(MAKE) -C $(FTLIB_DIR) --silent clean
	@[ -d ./objs ] && rm -rf ./objs || echo Object directory doesn\'t exist

fclean: clean
	@$(MAKE) -C $(FTLIB_DIR) --silent fclean
	@[ -f ./$(NAME) ] && rm $(NAME) || echo Program $(NAME) isn\'t compiled
	@[ -f ./$(NAMEB) ] && rm $(NAMEB)|| echo Bonus $(NAMEB) isn\'t compiled

re: fclean all

.PHONY: all bonus clean fclean re