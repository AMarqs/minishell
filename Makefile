NAME = minishell
LIBFT = ./libft

HEADERS = -I $(LIBFT)
LIBRARIES = $(LIBFT)/libft.a

SRCS = 	main.c \
		parse.c \
		group.c \
		utils.c \
		free_errors.c \
		built-ins/export.c \
		built-ins/unset.c \
		built-ins/env.c \
		built-ins/pwd.c \
		built-ins/cd.c \
		built-ins/echo.c \
		built-ins/exit.c \
		exec/exec_main.c \
		exec/fd_handler.c \
		exec/redirections.c \
		exec/heredoc.c \
		signals/signal_init.c \
		signals/signal_handler.c \
		signals/signal_utils.c

SRC = $(addprefix src/, $(SRCS))
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror -Ofast -g
CC = clang

all: $(NAME)

$(NAME): $(OBJ) libft
	@$(CC) $(FLAGS) -lreadline -gdwarf-4 $(OBJ) $(LIBRARIES) $(HEADERS) -o $(NAME)
	
%.o: %.c
	$(CC) $(FLAGS) -gdwarf-4 -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $< \n)"

libft:
	@make -C $(LIBFT)

clean:
	@rm -rf $(OBJ)
	@make fclean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
