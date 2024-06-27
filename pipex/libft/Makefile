##### Executable program's name ###############################################
NAME = libft.a

##### Define path and variables ###############################################
###############################################################################
CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
AR = ar rcs

##### Define source files and objects #########################################
###############################################################################
SRC = ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_itoa.c \
	ft_split.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_printf.c ft_printf_adress.c ft_printf_char.c ft_printf_digit.c ft_printf_string.c\
	
HEADER = libft.h 
OBJ= $(SRC:.c=.o)

##### Rule by default #########################################################
###############################################################################
all: $(NAME)

##### Create objectc (.o) from source fils (.c )###############################
###############################################################################
%.o: %.c
	@$(CC) -c $(CFLAGS) -I$(HEADER) $< -o $@

##### Linking objects in executable ###########################################
###############################################################################
$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

##### Clean objects ###########################################################
###############################################################################
clean:
	@$(RM) -r *.o

##### Clean executable ########################################################
###############################################################################
fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re