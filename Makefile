# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maquentr <maquentr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/02 13:05:22 by maquentr          #+#    #+#              #
#    Updated: 2022/01/04 14:30:02 by maquentr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME=pipex

CC=gcc

CFLAGS=-Wall -Wextra -Werror

RM=rm -f

INC=pipex.h

SRC=ft_split.c \
	ft_strlen.c \
	ft_strjoin.c \
	ft_join.c \
	ft_substr.c \
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
