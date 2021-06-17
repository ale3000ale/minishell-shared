/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_libft.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:32:19 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/14 16:35:16 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_table_len(char **table)
{
	int	i;

	if (!table)
		return (0);
	i = 0;
	while (table[i])
		i++;
	return (i);
}

int	free_table(char **table)
{
	int	i;

	if (table)
	{
		i = ft_table_len(table);
		while (--i >= 0)
			free(table[i]);
		free(table);
	}
	return (1);
}

/* ft_strlen from get_next_line */

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (i < n - 1 && s1[i] && (s1[i] == s2[i]))
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	my_clear_screen(void)
{
	printf("\e[1;1H\e[2J");
}

char	*ft_strdup(char *s)
{
	return (ft_strjoin("", s));
}
