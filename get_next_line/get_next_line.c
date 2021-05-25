/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:25:56 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/25 19:52:39 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	switch_special(char *buff)
{
	if (!ft_strncmp(buff, SS_UP, 4))
		write(1, "OO", 2);
	else if (!ft_strncmp(buff, SS_DOWN, 4))
		write(1, "AO", 2);
	else if (!ft_strncmp(buff, SS_RIGHT, 6))
		write(1, "SS", 2);
	else if (!ft_strncmp(buff, SS_LEFT, 6))
		write(1, "TN", 2);
	write(1, buff, ft_strlen(buff));
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