# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 13:05:22 by maquentr          #+#    #+#              #
#    Updated: 2022/02/05 18:58:10 by maquentr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME=pipex

CC=gcc

CFLAGS=-g3 -Wall -Wextra -Werror -fsanitize=address

RM=rm -f

INC=pipex.h

SRC=ft_split.c \
	utils.c \
	utils2.c \
	parsing.c \
	main.c

OBJ=$(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INC)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
all: $(NAME)

bonus:
	@make	all	OBJ="$(OBJ)"

clean:
	$(RM) $(OBJ) pipex

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
