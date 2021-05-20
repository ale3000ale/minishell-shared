/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:25:56 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/20 17:31:14 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_joinf(char *s1, char *s2, int freem)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (freem == 1)
		free(s1);
	else if (freem == 2)
		free(s2);
	else if (freem > 2)
	{
		free(s1);
		free(s2);
	}
	return (result);
}

void	ft_init_vars(int *flag, int *count, char **buff, char *c)
{
	*count = 0;
	*buff = (char *)malloc(sizeof(char) * (129));
	*flag = 1;
	*c = '\0';
}

int	ft_read(int fd, char **line)
{
	char	str[2];
	char	*buff;
	int		count;
	int		flag;

	ft_init_vars(&flag, &count, &buff, &str[1]);
	str[0] = 'c';
	while (flag > 0 && str[0] != '\n')
	{
		flag = read(fd, str, 1);
		if (flag > 0 && str[0] != '\n')
		{
			buff[count] = str[0];
			count++;
		}
		if (flag == 0 || count == 128 || str[0] == '\n')
		{
			buff[count] = '\0';
			*line = ft_joinf(*line, buff, 1);
			count = 0;
		}
	}
	free(buff);
	return (flag);
}

int	get_next_line(int fd, char **line)
{
	int	result;

	if (fd < 0 || !line)
		return (-1);
	*line = (char *)malloc(sizeof(char));
	*line[0] = '\0';
	result = ft_read(fd, line);
	if (result > 0)
		result = 1;
	return (result);
}
