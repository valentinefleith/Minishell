###############################################################################
#### executable program's name ################################################
NAME = pipex

NAME_BONUS = pipex_bonus
###############################################################################
#### path and variables #######################################################
###############################################################################
SRC_DIR = ./src/
OBJ_DIR = ./obj/
INCLUDE = ./include/

SRC_BONUS_DIR = ./bonus/
OBJ_BONUS_DIR = ./obj/
HEADER_BONUS = -I$(INCLUDE) -I$(LIBFT_DIR) -I$(GNL_DIR)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

GNL_DIR = ./bonus/get_next_line/
GNL = $(GNL_DIR)/get_next_line.a

HEADER = -I$(INCLUDE) -I$(LIBFT_DIR)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

GREEN = \033[0;32m
BOLD = \033[1m
RESET = \033[0;m

########### source files and objects ##########################################
###############################################################################
SRC_FILES = main.c utils.c linked_list_func.c parsing.c checking_access.c \
	cleaning.c pipex.c

OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

SRC_BONUS = main_bonus.c utils_bonus.c parsing_bonus.c checking_access_bonus.c \
		cleaning_bonus.c pipex_bonus.c linked_list_func_bonus.c

OBJ_BONUS = $(addprefix $(OBJ_BONUS_DIR), $(SRC_BONUS:.c=.o))

#### rule by default ##########################################################
###############################################################################
all: $(NAME)

#### create objects (.o) from source files (.c) ###############################
###############################################################################
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE) -c $< -o $@

$(OBJ_BONUS_DIR)%.o: $(SRC_BONUS_DIR)%.c
	@$(CC) $(CFLAGS) $(HEADER_BONUS) -c $< -o $@

#### linking objects in executable ############################################
###############################################################################
$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(HEADER) $(OBJ) $(LIBFT) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)$(BOLD)Compilation success [PIPEX]$(RESET)"

##### compile external libraries ##############################################
###############################################################################
$(LIBFT):
	@make --silent -C $(LIBFT_DIR)
	@echo "$(GREEN)$(BOLD)Compilation success [LIBFT]$(RESET)"

$(GNL):
	@make --silent -C $(GNL_DIR)
	@echo "$(GREEN)$(BOLD)Compilation success [GNL]$(RESET)"

###############################################################################
####### compile bonus #########################################################
$(NAME_BONUS): $(LIBFT) $(GNL) $(OBJ_BONUS)
	@$(CC) $(HEADER_BONUS) $(OBJ_BONUS) $(LIBFT) $(GNL) $(CFLAGS) -o $(NAME_BONUS)
	@echo "$(GREEN)$(BOLD)Compilation success [BONUS]$(RESET)"

##### Clean objects + external lib ############################################
###############################################################################
clean:
	@$(RM) -r $(OBJ_DIR)/*.o
	@$(RM) here_doc
	@make -C $(LIBFT_DIR) clean
	@make -C $(GNL_DIR) clean

##### Clean the executable + same for external lib ############################
###############################################################################
fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)
	@make -C $(LIBFT_DIR) fclean
	@make -C $(GNL_DIR) fclean

###############################################################################

re: fclean all

.PHONY: all clean fclean re valgrind valgrind_fd

##############################################################################

exec: clean all
	./$(NAME)

#ARGS = infile.txt "grep Now" "/usr/bin/cat" outfile.txt
#ARGS = infile.txt outfile.txt
#ARGS = here_doc lim cat cat  outfile.txt
ARGS = infile.txt date "man env" cat "grep -i exit" outfile.txt

log: CFLAGS += -D LOG
log: clean all
	./$(NAME)

valgrind: $(NAME_BONUS)
	@valgrind --leak-check=full --show-leak-kinds=all -s \
 		--trace-children=yes --track-origins=yes \
	./$(NAME_BONUS) $(ARGS)

valgrind_fd: $(NAME_BONUS)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s \
 		--trace-children=yes --track-fds=yes \
	./$(NAME_BONUS) $(ARGS)

valgrind_small: all
	@valgrind --track-fds=yes --trace-children=yes \
	./$(NAME) $(ARGS)