/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:56:33 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/24 11:49:36 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H

# define HISTORY		".history"

# define NEXT			1
# define PREC			-1

void	close_history(t_history *history);
void	history_change(t_history *history, char *line);
char	*get_history(int dir, t_history *history);
int		append_history(t_history *history);
void	open_history(t_term *term);
void	move_history(t_term *term, int dir);
void 	print_history(t_clist *cls);

#endif