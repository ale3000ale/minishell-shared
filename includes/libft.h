/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:25:33 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/03 18:54:01 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include "minishell.h"

char			**ft_split(char const *s, char c);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				free_table(char **table);
char			*find_path(void);
int				change_path(char *new_path);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
char			**ft_strcut(char *s, int pos);
int				ft_strdigit(char *s);
int				ft_putstr_fd(char *s, int fd);
char			*ft_itoa(int n);
int				ft_isdigit(int c);
long			ft_latoi(const char *str);
int				ft_atoi(const char *str);
char			*ft_strchr(const char *str, int c);
char			*ft_strnstr(const char *haystack, \
					const char *needle, size_t len);
int				ft_strccount(char *s, char c);
int				ft_strchrid(const char *str, int c);
size_t			mat_row(void **str);
int				ft_stralpha(char *s);
int				ft_isalpha(int c);

#endif
