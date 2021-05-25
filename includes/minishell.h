/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcarbone <gcarbone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:16:19 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/24 18:49:28 by gcarbone         ###   ########.fr       */
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

typedef struct	s_op
{
	int				key;
	char			*input;
	int				error;
	struct s_op		*next;
}				t_op;

typedef struct	s_queue
{
	t_op			*first;
}				t_queue;

typedef struct s_term
{
	char			*type;
	struct termios	dconf;
	struct termios	cconf;
	t_queue			queue;
}	t_term;

#endif