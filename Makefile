# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mobrycki <mobrycki@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/20 17:11:47 by dlanotte          #+#    #+#              #
#    Updated: 2021/06/16 17:00:00 by mobrycki         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_OFF	= "\033[0m"       # Text Reset
RED			= "\033[0;31m"    # Red
YELLOW		= "\033[0;33m"    # Yellow


NAME	=	minishell

CC		=	gcc

DFLAGS	=	-Wall -Wextra -Werror -g

CFLAGS	=	-Wall -Wextra -Werror

LIBFT	=	minilibft/ft_split.c \
			minilibft/ft_utils_libft.c \
			minilibft/ft_path_utils.c \
			minilibft/ft_strjoin.c \
			minilibft/ft_calloc.c \
			minilibft/ft_bzero.c \
			minilibft/ft_memcpy.c \
			minilibft/ft_strlen.c \
			minilibft/ft_strcut.c\
			minilibft/ft_strcpy.c\
			minilibft/ft_itoa.c\
			minilibft/ft_putstr.c\
			minilibft/ft_strdigit.c\
			minilibft/ft_atoi.c	\
			minilibft/ft_strfind.c\
			minilibft/mat_row.c\
			minilibft/ft_stralpha.c\
			minilibft/mat_join_row.c\
			minilibft/mat_init.c	\
			minilibft/ft_lstadd_back.c	\
			minilibft/ft_lstadd_front.c	\
			minilibft/ft_lstclear.c	\
			minilibft/ft_lstdelone.c\
			minilibft/ft_lstiter.c	\
			minilibft/ft_lstlast.c	\
			minilibft/ft_lstnew.c	\
			minilibft/ft_lstsize.c

GNL		= 	get_next_line/get_next_line.c \
			get_next_line/utils_gnl.c \
			get_next_line/cursor.c

GRAPH	=	graphic_functions/graphic_main.c

COMMAND	=	commands/easy_cmd.c\
			commands/env_cmd.c	\
			commands/common_cmd.c\
			commands/utils.c

HISTORY	=	history/history.c

SRC		=	${GRAPH} ${GNL} ${LIBFT} ${COMMAND} ${HISTORY} main.c utils.c parsing.c parsing_3.c

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
	@ echo "  amarcell | gcarbone | dlanotte"$(RED)"▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░ " $(COLOR_OFF)
	@ echo "  flwang   | mobrycki | fd-agnes"$(RED)"░  ░░ ░   ░     ░ ░     ░ ░    " $(COLOR_OFF)
	@ echo "                               "$(RED)" ░  ░  ░   ░  ░    ░  ░    ░  ░ " $(COLOR_OFF)           
	@ echo ""
	#@ say -v Alice benvenuto in asci hell, premi enter per continuare      
	@ read -p "Done. Press enter to continue..."

slim: 
	@ $(CC) -g $(SRC) -o $(NAME)
	@ make clean
	@ echo ""
	@ echo $(YELLOW)" SLIM SLIM SLIM SLIM SLIM SLIM SLIM SLIM SLIM SLIM SLIM SLIM  " $(COLOR_OFF)
	@ echo "   █████  ███████  ██████ ██ ██"$(RED)" ██░ ██ ▓█████  ██▓     ██▓     " $(COLOR_OFF)
	@ echo "  ██   ██ ██      ██      ██ ██"$(RED)"▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒     " $(COLOR_OFF)
	@ echo "  ███████ ███████ ██      ██ ██"$(RED)"▒██▀▀██░▒███   ▒██░    ▒██░     " $(COLOR_OFF)
	@ echo "  ██   ██      ██ ██      ██ ██"$(RED)"░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░     " $(COLOR_OFF)
	@ echo "  ██   ██ ███████  ██████ ██ ██"$(RED)"░▓█▒░██▓░▒████▒░██████▒░██████▒ " $(COLOR_OFF)
	@ echo "                               "$(RED)" ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░ " $(COLOR_OFF)
	@ echo "  amarcell | gcarbone | dlanotte"$(RED)"▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░ " $(COLOR_OFF)
	@ echo "  flwang   | mobrycki | fd-agnes"$(RED)"░  ░░ ░   ░     ░ ░     ░ ░    " $(COLOR_OFF)
	@ echo "                               "$(RED)" ░  ░  ░   ░  ░    ░  ░    ░  ░ " $(COLOR_OFF)           
	@ echo $(YELLOW)" SLIM SLIM SLIM SLIM SLIM SLIM SLIM SLIM SLIM SLIM SLIM SLIM  " $(COLOR_OFF)
	@ echo ""
	@ read -p "Done. Press enter to continue..."

debug: 
	@ $(CC) $(DFLAGS) $(SRC) -o $(NAME)
	@ make clean
	@ echo ""
	@ echo $(YELLOW)" DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG  " $(COLOR_OFF)
	@ echo "   █████  ███████  ██████ ██ ██"$(RED)" ██░ ██ ▓█████  ██▓     ██▓     " $(COLOR_OFF)
	@ echo "  ██   ██ ██      ██      ██ ██"$(RED)"▓██░ ██▒▓█   ▀ ▓██▒    ▓██▒     " $(COLOR_OFF)
	@ echo "  ███████ ███████ ██      ██ ██"$(RED)"▒██▀▀██░▒███   ▒██░    ▒██░     " $(COLOR_OFF)
	@ echo "  ██   ██      ██ ██      ██ ██"$(RED)"░▓█ ░██ ▒▓█  ▄ ▒██░    ▒██░     " $(COLOR_OFF)
	@ echo "  ██   ██ ███████  ██████ ██ ██"$(RED)"░▓█▒░██▓░▒████▒░██████▒░██████▒ " $(COLOR_OFF)
	@ echo "                               "$(RED)" ▒ ░░▒░▒░░ ▒░ ░░ ▒░▓  ░░ ▒░▓  ░ " $(COLOR_OFF)
	@ echo "  amarcell | gcarbone | dlanotte"$(RED)"▒ ░▒░ ░ ░ ░  ░░ ░ ▒  ░░ ░ ▒  ░ " $(COLOR_OFF)
	@ echo "  flwang   | mobrycki | fd-agnes"$(RED)"░  ░░ ░   ░     ░ ░     ░ ░    " $(COLOR_OFF)
	@ echo "                               "$(RED)" ░  ░  ░   ░  ░    ░  ░    ░  ░ " $(COLOR_OFF)           
	@ echo $(YELLOW)" DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG DEBUG  " $(COLOR_OFF)
	@ echo ""
	@ say -v Alice benvenuto in asci hell versione debag      
	@ read -p "Done. Press enter to continue..."

clean:   
	@ rm -f ${OBJ}

fclean: clean
	@ rm -f $(NAME)
	@ rm -f ${OBJ}
	@ echo ""
	@ echo "fclean completed."

debug-clean: fclean
	@ rm -dir -f minishell.dSYM
	@ echo "debug-clean completed."

re: fclean all debug slim