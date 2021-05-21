# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zxcvbinz <zxcvbinz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:11:47 by dlanotte          #+#    #+#              #
#    Updated: 2021/05/21 23:15:37 by zxcvbinz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

LIBFT	=	minilibft/ft_split.c \
			minilibft/ft_utils_libft.c \
			minilibft/ft_path_utils.c

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
	@ echo "███╗░░░███╗██╗███╗░░██╗██╗░██████╗██╗░░██╗███████╗██╗░░░░░██╗░░░░░"
	@ echo "██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░"
	@ echo "██╔████╔██║██║██╔██╗██║██║╚█████╗░███████║█████╗░░██║░░░░░██║░░░░░"
	@ echo "██║╚██╔╝██║██║██║╚████║██║░╚═══██╗██╔══██║██╔══╝░░██║░░░░░██║░░░░░"
	@ echo "██║░╚═╝░██║██║██║░╚███║██║██████╔╝██║░░██║███████╗███████╗███████╗"
	@ echo "╚═╝░░░░░╚═╝╚═╝╚═╝░░╚══╝╚═╝╚═════╝░╚═╝░░╚═╝╚══════╝╚══════╝╚══════╝"
	@ echo ""
	@ read -p "Done. Press enter for continue...."
	@ ./minishell
clean:
	@ rm -f ${OBJ}

fclean: clean
	@ rm -f $(NAME)
	@ rm -f ${OBJ}
	@ echo ""
	@ echo "fclean completed."

re: fclean all