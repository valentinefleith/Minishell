# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 15:31:12 by vafleith          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2024/07/02 13:30:03 by vafleith         ###   ########.fr        #
=======
#    Updated: 2024/07/02 15:25:18 by luvallee         ###   ########.fr        #
>>>>>>> main
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra
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

<<<<<<< HEAD
SRCS = main.c \
	   pipex/checking_access.c pipex/cleaning.c pipex/linked_list_func.c \
	   pipex/parsing.c pipex/pipex.c pipex/utils.c\
	   parsing/parse_prompt.c parsing/parse_cmd.c parsing/bash_error_messages.c \
	   parsing/handle_quotes.c \
	   free/ft_free_tab.c free/free_and_exit.c \
	   execution/execute_command.c

=======
SRCS = main.c $(PIPEX_SRCS) $(PARSING_SRCS) \
	builtin/builtin.c builtin/error_builtin.c builtin/parse_builtin.c
>>>>>>> main
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