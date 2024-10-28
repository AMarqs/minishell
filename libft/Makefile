# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 14:55:07 by glopez-c          #+#    #+#              #
#    Updated: 2024/10/03 20:55:20 by glopez-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

AR = ar rcs

RM = rm -f

CC = gcc
CCFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC_PATH = ./sources/
OBJ_PATH = ./objects/

SRC = ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha \
	ft_isascii ft_isdigit ft_isprint ft_itoa ft_memchr \
	ft_memcmp ft_memcpy ft_memmove ft_memset ft_putchar_fd \
	ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split ft_strchr \
	ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy \
	ft_strlen ft_strmapi ft_strncmp ft_strnstr ft_strrchr \
	ft_strtrim ft_substr ft_tolower ft_toupper
	# ft_printf/ft_printf ft_printf/ft_printchar_fd ft_printf/ft_printnbr_base_fd \
	# ft_printf/ft_printnbr_fd ft_printf/ft_printstr_fd

BSRC = ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus \
	ft_lstlast_bonus ft_lstadd_back_bonus ft_lstdelone_bonus \
	ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus

SRCC = $(addsuffix .c, ${SRC})
SRCS = $(addprefix $(SRC_PATH), $(SRCC))

BSRCC = $(addsuffix .c, ${BSRC})
BSRCS = $(addprefix $(SRC_PATH), $(BSRCC))

OBJ = $(SRCC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

BOBJ = $(BSRCC:.c=.o)
BOBJS = $(addprefix $(OBJ_PATH), $(BOBJ))

INC = -I ./includes/

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
RED = \033[0;31m
RESET = \033[0m

# Animation

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@printf "$(YELLOW)Compiling $<...$(RESET)\n"
	@${CC} ${CCFLAGS} ${INC} -c $< -o $@
	@printf "$(GREEN)Compiled $< successfully!$(RESET)\n"

all:  ${NAME}

$(NAME): ${OBJS}
	@printf "$(BLUE)Creating archive $@...$(RESET)\n"
	@${AR} ${NAME} ${OBJS}
	@printf "$(GREEN)Archive $@ created successfully!$(RESET)\n"

bonus:  ${BOBJS}
	@printf "$(BLUE)Creating bonus archive $@...$(RESET)\n"
	@${AR} ${NAME} ${BOBJS}
	@printf "$(GREEN)Bonus archive $@ created successfully!$(RESET)\n"

clean: 
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@${RM} ${OBJS} ${BOBJS}
	@printf "$(GREEN)Object files cleaned!$(RESET)\n"

fclean: clean
	@printf "$(RED)Cleaning archive...$(RESET)\n"
	@${RM} ${NAME}
	@printf "$(GREEN)Archive cleaned!$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re bonus