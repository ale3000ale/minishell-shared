# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zxcvbinz <zxcvbinz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:11:47 by dlanotte          #+#    #+#              #
#    Updated: 2021/05/26 00:13:16 by zxcvbinz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_OFF	= "\033[0m"       # Text Reset
RED			= "\033[0;31m"    # Red
YELLOW		= "\033[0;33m"    # Yellow


NAME	=	minishell

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g

LIBFT	=	minilibft/ft_split.c \
			minilibft/ft_utils_libft.c \
			minilibft/ft_path_utils.c \
			minilibft/ft_strjoin.c \
			minilibft/ft_calloc.c \
			minilibft/ft_bzero.c \
			minilibft/ft_memcpy.c \
			minilibft/ft_strlen.c \

GNL		= 	get_next_line/get_next_line.c \

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
	@ echo ""
	@ echo "   █████  ███████  ██████ ██ ██"$(RED)" ██░ ██ ▓█████  ██▓     ██▓     " $(COLOR_OFF)
	@ echo "  ██   ██ ██      ██      ██ ██"$(RED)"▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒     " $(COLOR_OFF)
	@ echo "  ███████ ███████ ██      ██ ██"$(RED)"▒██▀▀██░▒███   ▒██░    ▒██░     " $(COLOR_OFF)
	@ echo "  ██   ██      ██ ██      ██ ██"$(RED)"░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░     " $(COLOR_OFF)
	@ echo "  ██   ██ ███████  ██████ ██ ██"$(RED)"░▓█▒░██▓░▒████▒░██████▒░██████▒ " $(COLOR_OFF)
	@ echo "                               "$(RED)" ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░ " $(COLOR_OFF)
	@ echo "  dlanotte | amarcell | gcarbone"$(RED)"▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░ " $(COLOR_OFF)
	@ echo "  fd-agnes | flwang   | mobrycki"$(RED)"░  ░░ ░   ░     ░ ░     ░ ░    " $(COLOR_OFF)
	@ echo "                               "$(RED)" ░  ░  ░   ░  ░    ░  ░    ░  ░ " $(COLOR_OFF)           
	@ echo ""      
	@ read -p "Done. Press enter to continue...."
clean:   
	@ rm -f ${OBJ}

fclean: clean
	@ rm -f $(NAME)
	@ rm -f ${OBJ}
	@ echo ""
	@ echo "fclean completed."

re: fclean all
       