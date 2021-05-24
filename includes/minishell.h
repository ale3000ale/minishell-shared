/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:16:19 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/24 16:28:30 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/errno.h>
# include <stdlib.h>
# include <curses.h>
# include <termios.h>
# include "graphic.h"
# include "get_next_line.h"
# include "libft.h"
# include "my_main_functions.h"
# include "commands.h"

typedef struct s_term
{
	char			*type;
	struct termios	dconf;
	struct termios	cconf;
}	t_term;

#endif