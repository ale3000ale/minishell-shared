/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:53:57 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/11 15:58:47 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <termios.h>

typedef struct s_op
{
	int					key;
	char				*input;
	int					error;
	struct s_op			*next;
}				t_op;

typedef struct s_queue
{
	t_op			*first;
	int				size;
}				t_queue;

typedef struct s_clist
{
	void			*content;
	struct s_clist	*next;
	struct s_clist	*pre;
	int				last;
}				t_clist;

typedef struct s_history
{
	int		fd;
	t_clist	*history;
	int		count_new;
}	t_history;

typedef struct s_term
{
	char			*type;
	struct termios	dconf;
	struct termios	cconf;
	t_queue			queue;
	char			*input;
	int				cursor; // indice del cursore
	int				last_status;
	t_history		history;
}	t_term;



#endif