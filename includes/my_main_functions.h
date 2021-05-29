/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:54:25 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/29 17:37:50 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MAIN_FUNCTIONS_H
# define MY_MAIN_FUNCTIONS_H

# define PATH_MAX	4096 
# include "struct.h"

void	init(t_term *term);
int		find_command(t_term *term);
void	ft_signal_manager(void);
void	my_clear_screen(void);
int		ft_parsing_hub(int index_commands, char *line, char **commands);
void	ft_execute_commands(int commands, char *line);

#endif