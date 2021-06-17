/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_main_functions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobrycki <mobrycki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:54:25 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/17 11:48:37 by mobrycki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MAIN_FUNCTIONS_H
# define MY_MAIN_FUNCTIONS_H

# define PATH_MAX	4096 
# include "struct.h"

void	init(t_term *term, char **env);
int		find_command(t_term *term);
void	ft_signal_manager(void);
void	my_clear_screen(void);
int		ft_parsing_hub(t_term *term);
void	ft_execute_commands(t_clist *queque, t_term *term, int pid);
void	exec_manager(t_clist *queque, t_term *term);
t_op	*get_op(t_clist *cls);
char	*ft_translate(char *input, char **env);
char	*ft_dollar(char **input, char **env, char **trans, int *iter);

#endif
