# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:11:47 by dlanotte          #+#    #+#              #
#    Updated: 2021/05/20 17:32:00 by dlanotte         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

LIBFT = minilibft/

GNL = 	get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c

GRAPH = graphic_functions/graphic_main.c

SRC = ${GRAPH} ${GNL} main.c

OBJ := ${SRC:.c=.o}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
	
$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)
	make clean

clean:
	rm -f ${OBJ}

fclean: clean
	rm -f $(NAME)
	rm -f ${OBJ}

re: fclean all