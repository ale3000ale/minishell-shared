/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:42:42 by amarcell          #+#    #+#             */
/*   Updated: 2021/05/26 16:45:15 by amarcell         ###   ########.fr       */
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

# define SS_LEFT				"\e[D"
# define SS_RIGHT				"\e[C"
# define SS_UP					"\e[A"
# define SS_DOWN				"\e[B"

# define SHIFT_SS_LEFT			"\e[1;2D"
# define SHIFT_SS_RIGHT			"\e[1;2C"

# define SS_DEL					127
/* FUNCTIONS */

void	error404(char *line);
void	quit(void);

#endif
