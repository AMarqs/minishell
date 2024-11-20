NAME = minishell
LIBFT = ./libft

HEADERS = -I $(LIBFT)
LIBRARIES = $(LIBFT)/libft.a

SRCS = 	main.c \
		tester.c \
		utils1.c \
		utils2.c \
		environment/environment.c \
		environment/env_variable.c \
		environment/env_shlvl.c \
		parse/parse.c \
		parse/token.c \
		parse/group.c \
		parse/group_utils.c \
		parse/group_errors.c \
		parse/group_char.c \
		parse/group_redir.c \
		parse/group_var.c \
		built-ins/cd.c \
		built-ins/echo.c \
		built-ins/env.c \
		built-ins/exit.c \
		built-ins/export.c \
		built-ins/export_utils.c \
		built-ins/export_env.c \
		built-ins/pwd.c \
		built-ins/unset.c \
		exec/exec_main.c \
		exec/fd_handler.c \
		exec/redirections.c \
		exec/heredoc.c \
		errors/frees.c \
		errors/errors.c \
		signals/signal_init.c \
		signals/signal_handler.c \
		signals/signal_utils.c \
		printf_BORRAR.c

SRC = $(addprefix src/, $(SRCS))
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

FLAGS = -Wall -Wextra -Werror -Ofast -g
CC = clang

all: $(NAME)

$(NAME): $(OBJ) libft
	@$(CC) $(FLAGS) -lreadline -gdwarf-4 $(OBJ) $(LIBRARIES) $(HEADERS) -o $(NAME)
	
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS) -gdwarf-4 -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $< \n)"

libft:
	@make -C $(LIBFT)

clean:
	@rm -rf $(OBJ_DIR)
	@make fclean -C $(LIBFT)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
