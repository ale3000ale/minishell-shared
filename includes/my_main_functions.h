/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:54:25 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/09 18:57:18 by amarcell         ###   ########.fr       */
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
int		ft_parsing_hub(char *line, char **commands, t_term *term);
void	ft_execute_commands(char *cmd, char *line, t_term *term, int pipe);

#endif