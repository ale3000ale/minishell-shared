/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:56:33 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/10 18:34:13 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define HISTORY		"../.history"

# define NEXT			1
# define PREC			-1

typedef struct s_history
{
	int		fd;
	t_clist	*history;
	int		count_new;
}	t_history;

#endif