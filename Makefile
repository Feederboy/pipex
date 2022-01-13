# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 13:05:22 by maquentr          #+#    #+#              #
#    Updated: 2022/01/07 09:36:39 by matt             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME=pipex

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

INC=pipex.h

SRC=ft_split.c \
	utils.c \
	main.c

OBJ=$(SRC:.c=.o)


%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INC)

$(NAME): $(OBJ)
	ar rcs	$(NAME)	$(OBJ)

all: $(NAME)

bonus:
	@make	all	OBJ="$(OBJ)"

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
