/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 18:53:57 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/29 17:37:49 by dlanotte         ###   ########.fr       */
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

typedef struct s_term
{
	char			*type;
	struct termios	dconf;
	struct termios	cconf;
	t_queue			queue;
	char			*input;
	int				cursor; // indice del cursore
}	t_term;

#endif