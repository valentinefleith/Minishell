###############################################################################
#### executable program's name ################################################

NAME = minishell

###############################################################################
#### path and variables #######################################################
###############################################################################

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
OBJ_DIR = build
INC = -I include/ -I$(LIBFT_PATH) -I$(GNL_PATH)

GNL_PATH = ./get_next_line
GNL_NAME = get_next_line.a
GNL = $(GNL_PATH)/$(GNL_NAME)

LIBFT_PATH = ./libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)/$(LIBFT_NAME)

READFLAGS = readline

GREEN = \033[0;32m
BLUE = \033[34m
VIOLET = \033[35m
BOLD = \033[1m
RESET = \033[0;m

###############################################################################
#### source files and objects #################################################
###############################################################################

PARSING_FILES = parsing/lexing/lexing.c parsing/lexing/tokens_destructor.c \
			parsing/lexing/tokens_constructor.c parsing/lexing/tokens_get.c \
			parsing/lexing/quotes_removing.c parsing/lexing/var_expansion.c \
			parsing/lexing/var_expansion_utils.c parsing/lexing/tokens_print.c \
			parsing/btree/btree_ast_build.c parsing/btree/btree_constructor.c \
			parsing/btree/btree_destructor.c parsing/btree/btree_print.c \
			parsing/btree/btree_properties.c \
			parsing/parser/operation.c \
			parsing/parser/parser_utils.c parsing/parser/parser.c \
			parsing/parser/parsing_table.c parsing/parser/operation_utils.c \

BUILTIN_FILES = builtin/builtins_manager.c builtin/ft_cd.c builtin/ft_echo.c \
			builtin/ft_env.c builtin/ft_exit.c builtin/ft_export.c \
			builtin/ft_export_utils.c builtin/ft_pwd.c builtin/ft_unset.c \
			builtin/ft_exit_utils.c builtin/builtin_utils.c

ENV_FILES = env/env_refresh.c env/env_utils.c env/env.c \

EXECUTION_FILES = execution/exec_utils.c execution/execution.c \
			execution/get_path.c execution/pipeline.c execution/redirection.c \
			execution/signal_handler.c \

SECURITY_FILES = security/alloc_errors.c security/builtin_errors.c \
			security/file_error.c security/free_and_exit.c \
			security/ft_free_tab.c security/parser_error.c \
			security/free_env.c security/error_execution.c security/error_paths.c

SRCS =  main.c $(PARSING_FILES) $(BUILTIN_FILES) $(ENV_FILES) $(EXECUTION_FILES) $(SECURITY_FILES)


SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

###############################################################################
#### rule by default ##########################################################
###############################################################################

all: $(LIBFT) $(GNL) $(NAME)

###############################################################################
#### create objects (.o) from source files (.c) ###############################
###############################################################################
	
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INC)

###############################################################################
#### linking objects in executable ############################################
###############################################################################

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(GNL) $(INC) -l$(READFLAGS)
	@echo "$(GREEN)$(BOLD)Minishell is ready ✔$(RESET)"

###############################################################################
#### compile external libraries ###############################################
###############################################################################

$(LIBFT):
	@make -C $(LIBFT_PATH) > /dev/null
	@echo "$(VIOLET)$(BOLD)Compilation success -> LIBFT$(RESET)"

$(GNL):
	@make -C $(GNL_PATH) > /dev/null
	@echo "$(VIOLET)$(BOLD)Compilation success -> GNL$(RESET)"

###############################################################################
#### Clean objects + external lib #############################################
###############################################################################

clean:
	@echo "$(BLUE)$(BOLD)Cleaning up object files 🧹$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make clean -C $(LIBFT_PATH) > /dev/null
	@make clean -C $(GNL_PATH) > /dev/null

###############################################################################
#### Clean the executable + external lib ######################################
###############################################################################

fclean: clean
	@make fclean -C $(LIBFT_PATH) > /dev/null
	@make fclean -C $(GNL_PATH) > /dev/null
	@rm -rf $(NAME)

###############################################################################
###############################################################################

re: fclean all

###############################################################################
###############################################################################

.PHONY: all clean fclean re

###############################################################################
###############################################################################

valgrind_flags: $(LIBFT) $(GNL) $(NAME)
	@valgrind --track-fds=yes --trace-children=yes \
		--leak-check=full --show-leak-kinds=all \
		--suppressions=fuck_readline \
	./$(NAME)
