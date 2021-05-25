/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:25:56 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/25 19:49:09 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Controlla se l'input è speciale */

static void	ft_three_bits(char *tab, int *wc)
{
	tab[0] = (*wc >> 12) + 0xE0;
	tab[1] = ((*wc >> 6) & 0x3F) + 0x80;
	tab[2] = (*wc & 0x3F) + 0x80;
}

static void	ft_four_bits(char *tab, int *wc)
{
	tab[0] = (*wc >> 18) + 0xF0;
	tab[1] = ((*wc >> 12) & 0x3F) + 0x80;
	tab[2] = ((*wc >> 6) & 0x3F) + 0x80;
	tab[3] = (*wc & 0x3F) + 0x80;
}

int			ft_putwchar_all(wchar_t wc, char *tab)
{
	int		nb;

	nb = (int)wc;
	ft_bzero(tab, 5);
	if ((int)wc < 0 || (((int)wc > 0xD7FF && (int)wc < 0xE000))
	|| ((int)wc > 0x10FFFF))
		return (-1);
	else if ((int)wc == 0)
		tab[0] = (int)wc + 1;
	else if ((int)wc <= 0x7F)
		tab[0] = (int)wc;
	else if ((int)wc <= 0x7FF)
	{
		tab[0] = ((int)wc >> 6) + 0xC0;
		tab[1] = ((int)wc & 0x3F) + 0x80;
	}
	else if ((int)wc <= 0xFFFF)
		ft_three_bits(tab, &nb);
	else if ((int)wc <= 0x10FFFF)
		ft_four_bits(tab, &nb);
	return (0);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (dst);
	if (src < dst && (src + n >= dst))
	{
		while (n > 0)
		{
			n--;
			*((char *)dst + n) = *((char *)src + n);
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			*((char *)dst + i) = *((char *)src + i);
			i++;
		}
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char *mem;

	if (!s1)
		return (NULL);
	mem = (char *)ft_calloc(ft_strlen(s1) + 1, sizeof(const char));
	if (mem)
		ft_memmove(mem, s1, ft_strlen(s1));
	return (mem);
}

static int	switch_special(char *buff)
{
	/* if (!ft_strncmp(buff, SS_UP, 4))
		write(1, "OO", 2);
	else if (!ft_strncmp(buff, SS_DOWN, 4))
		write(1, "AO", 2);
	else if (!ft_strncmp(buff, SS_RIGHT, 6))
		write(1, "SS", 2);
	else if (!ft_strncmp(buff, SS_LEFT, 6))
		write(1, "TN", 2); */
	char	*test;
	wchar_t	*wtab;
	char	*tab;
	int		i;

	i = -1;
	test = ft_strdup("");
	tab = (char *)malloc(5 * sizeof(char));
	wtab = (wchar_t *) buff;
	while (!ft_putwchar_all(wtab[++i], tab) || i < 5)
	{
		if (wtab[i] == L'\0')
			break ;
		test = ft_strjoin(test, tab);
	}
	write(1, test, ft_strlen(test));
	return (1);
}

static void	check_char(char *buff, char **line)
{
	char	*temp;

	switch_special(buff);
	temp = *line;
	*line = ft_strjoin(temp, buff);
	free(temp);
}

int	get_next_line(int fd, char **line, t_term *term)
{
	char	buff[5];
	int		rd;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_calloc(1, 1);
	if (!(*line))
		return (-1);
	ft_bzero(buff, 5);
	tcsetattr(0, TCSANOW, &term->cconf);
	rd = read(fd, buff, 1) > 0;
	tcsetattr(0, TCSANOW, &term->dconf);
	while (rd)
	{
		if (buff[0] == '\n')
			return (1);
		if (rd == -1)
			return (-1);
		check_char(buff, line);
		ft_bzero(buff, 5);
		tcsetattr(0, TCSANOW, &term->cconf);
		rd = read(fd, buff, 1) > 0;
		tcsetattr(0, TCSANOW, &term->dconf);
	}
	return (0);
}
