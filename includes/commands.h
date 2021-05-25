/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:42:42 by amarcell          #+#    #+#             */
/*   Updated: 2021/05/25 19:36:02 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# define COMMANDS	"clear,env,echo,exit,cd"

# define MY_CLEAR			0
# define MY_ENV				1
# define MY_ECHO			2
# define MY_EXIT			3
# define MY_CD				4

/* SPECIAL */

# define SS_UP				"0xff52"
# define SS_DOWN			"\033[B"
# define SS_RIGHT			"^[[C"
# define SS_LEFT			"^[[D"

void	error404(char *line);
void	quit(void);

#endif