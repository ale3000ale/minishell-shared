/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zxcvbinz <zxcvbinz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:25:56 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/26 00:13:22 by zxcvbinz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	switch_special(char *buff)
{
	if (buff[0] == SS_MAIN && buff[2] == 'A')
		write(1, "UP", 2);
	else if (buff[0] == SS_MAIN && buff[2] == 'D')
		write(1, "LEFT", 5);
	else if (buff[0] == SS_MAIN && buff[2] == 'C')
		write(1, "RIGHT", 6);
	else if (buff[0] == SS_MAIN && buff[2] == 'B')
		write(1, "DOWN", 4);
	else
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
	char	buff[7];
	int		rd;

	if (fd < 0 || !line)
		return (-1);
	*line = ft_calloc(1, 1);
	if (!(*line))
		return (-1);
	ft_bzero(buff, 6);
	tcsetattr(0, TCSANOW, &term->cconf);
	rd = read(fd, buff, 6) > 0;
	tcsetattr(0, TCSANOW, &term->dconf);
	while (rd)
	{
		if (buff[0] == '\n')
			return (1);
		if (rd == -1)
			return (-1);
		check_char(buff, line);
		ft_bzero(buff, 6);
		tcsetattr(0, TCSANOW, &term->cconf);
		rd = read(fd, buff, 6) > 0;
		tcsetattr(0, TCSANOW, &term->dconf);
	}
	return (0);
}
