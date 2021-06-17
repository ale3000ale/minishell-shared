/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:56:33 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/11 19:32:23 by amarcell         ###   ########.fr       */
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
int		append_history(t_history *history, char *line);
void	open_history(t_term *term);
void	move_history(t_term *term, int dir);

#endif