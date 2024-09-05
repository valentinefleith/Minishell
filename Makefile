# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 15:31:12 by vafleith          #+#    #+#              #
#    Updated: 2024/09/05 17:33:15 by luvallee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -g
# CFLAGS += -Werror

LIBFT_PATH = libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)/$(LIBFT_NAME)

GNL_PATH = get_next_line
GNL_NAME = get_next_line.a
GNL = $(GNL_PATH)/$(GNL_NAME)

INC = -Iinclude -I$(LIBFT_PATH) -I$(GNL_PATH)
READFLAGS = readline

SRC_DIR = src

SRCS = main.c \
	   pipex/checking_access.c pipex/cleaning.c pipex/linked_list_func.c \
	   pipex/parsing.c pipex/pipex.c pipex/utils.c\
	   parsing/lexing/lexing.c parsing/lexing/tokens_constructor.c \
	   parsing/lexing/tokens_get.c parsing/lexing/tokens_destructor.c \
	   parsing/lexing/tokens_print.c parsing/lexing/var_expansion.c \
	   parsing/lexing/quotes_removing.c \
	   parsing/btree/btree_constructor.c parsing/btree/btree_properties.c \
	   parsing/btree/btree_destructor.c parsing/btree/btree_ast_build.c \
	   parsing/btree/btree_print.c \
	   parsing/parsing_table/parser.c parsing/parsing_table/parser_utils.c \
	   parsing/parsing_table/operation.c parsing/parsing_table/parser_debug.c \
	   parsing/parsing_table/parsing_table.c parsing/parsing_table/parsing_env_var.c \
	   env/env.c env/env_utils.c env/env_refresh.c \
	   free/ft_free_tab.c free/free_and_exit.c \
	   execution/exec_utils.c execution/redirection.c execution/execution.c \
	   execution/error_execution.c builtin/builtin.c \
	   builtin/ft_env.c builtin/ft_cd.c builtin/ft_pwd.c builtin/ft_echo.c builtin/ft_export.c \
	   builtin/ft_unset.c builtin/ft_exit.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ_DIR = build
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

.PHONY: all
all: $(LIBFT) $(GNL) $(NAME)

$(OBJ_DIR)/%.o: %.c
	@echo Compiling $<
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(LIBFT):
	@echo "Making Libft"
	@make -C $(LIBFT_PATH) > /dev/null
	
$(GNL):
	@echo "Making GNL"
	@make -C $(GNL_PATH) > /dev/null

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(GNL) $(INC) -l$(READFLAGS)
	@echo "minishell ready."

.PHONY: clean
clean:
	@echo Cleaning up object files	
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH) > /dev/null
	@make clean -C $(GNL_PATH) > /dev/null

.PHONY: fclean
fclean: clean
	@make fclean -C $(LIBFT_PATH) > /dev/null
	@make fclean -C $(GNL_PATH) > /dev/null
	@rm -rf $(NAME)

.PHONY: re
re: fclean all

valgrind_fd: $(NAME)
	@valgrind --track-fds=yes --trace-children=yes \
		--leak-check=full \
	./$(NAME) $(ARGS)