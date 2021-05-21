/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:42:42 by amarcell          #+#    #+#             */
/*   Updated: 2021/05/21 14:18:37 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# define COMMANDS	"clear,env,echo,exit"

# define CLEAR		0
# define ENV		1
# define ECHO		2
# define EXIT		3

void	error404(char *line);
void	quit(void);

#endif