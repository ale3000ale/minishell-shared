/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:25:33 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/28 13:15:17 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "minishell.h"

char			**ft_split(char const *s, char c);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			free_table(char **table);
char			*find_path(void);
int				change_path(char *new_path);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
char			**ft_strcut(char *s, int pos);

#endif
