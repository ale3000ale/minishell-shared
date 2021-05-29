/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 18:23:28 by gcarbone          #+#    #+#             */
/*   Updated: 2021/05/29 17:39:46 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include "struct.h"

int		get_next_line(int fd, t_term *term);
int		cursorforward(t_term *term);
int		cursorbackward(t_term *term);
int		echo_input(char *buff, t_term *term);
int		delete(t_term *term);
void	cursorto(int pos, t_term *term);
#endif
