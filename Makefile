# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 15:31:12 by vafleith          #+#    #+#              #
#    Updated: 2024/06/29 14:22:35 by vafleith         ###   ########.fr        #
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

PIPEX_DIR = pipex
PIPEX_SRCS = checking_access.c cleaning.c linked_list_func.c parsing.c pipex.c \
			 utils.c
PIPEX_SRCS := $(addprefix $(PIPEX_DIR)/, $(PIPEX_SRCS))

PARSING_DIR = parsing
PARSING_SRCS = parse_prompt.c
PARSING_SRCS := $(addprefix $(PARSING_DIR)/, $(PARSING_SRCS))

SRC_DIR = src

SRCS = main.c $(PIPEX_SRCS) $(PARSING_SRCS)
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
