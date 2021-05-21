# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:11:47 by dlanotte          #+#    #+#              #
#    Updated: 2021/05/21 12:37:35 by amarcell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

LIBFT	=	minilibft/ft_split.c \
		minilibft/ft_utils_libft.c

GNL		= 	get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c

GRAPH	=	graphic_functions/graphic_main.c

COMMAND	=	commands/easy_cmd.c

SRC		=	${GRAPH} ${GNL} ${LIBFT} ${COMMAND} main.c utils.c

OBJ := ${SRC:.c=.o}

%.o: %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
	
$(NAME): $(OBJ)
	@ $(CC) $(CFLAGS) $(SRC) -o $(NAME)
	@ make clean

clean:
	@ rm -f ${OBJ}

fclean: clean
	@ rm -f $(NAME)
	@ rm -f ${OBJ}

re: fclean all