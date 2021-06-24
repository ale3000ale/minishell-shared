/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:38:35 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/21 17:01:40 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# define	EMPTY			0
# define	OVERWRITE		1
# define	JOIN			2

int		ft_unsetenv(char *name, char **env);
int		ft_setenv(char *name, char *content, int option, t_term *terms);
char	*ft_getenv(char *name, char **env);
#endif