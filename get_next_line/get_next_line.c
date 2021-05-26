/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:25:56 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/26 18:20:12 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	switch_special(char *buff, t_term *term)
{
	/*int i = 0;
	while (buff[i])
		printf ("%d ", buff[i++]);
	printf("\n");*/
	if (!ft_strncmp(SS_UP, buff, 7))
		write(1, "UP", 2);
	else if (!ft_strncmp(SS_LEFT, buff, 7))
		cursorbackward(term);
	else if (!ft_strncmp(SS_RIGHT, buff, 7))
		cursorforward(term);
	else if (!ft_strncmp(SS_DOWN, buff, 7))
		write(1, "DOWN", 4);
	else if (!ft_strncmp(SHIFT_SS_LEFT, buff, 7))
		write(1, "S_LEFT", 7);
	else if (!ft_strncmp(SHIFT_SS_RIGHT, buff, 7))
		write(1, "S_RIGHT", 7);
	else if (buff[0] == SS_DEL && !buff[1])
		return (2);
	else
		return (echo_input(buff, term));
	return (1);
}

static void	check_char(char *buff, t_term *term)
{
	int		ret;

	ret = switch_special(buff, term);
}

int	get_next_line(int fd, t_term *term)
{
	char	buff[7];
	int		rd;

	if (fd < 0)
		return (-1);
	term->input = ft_calloc(1, 1);
	if (!(term->input))
		return (-1);
	rd = 1;
	term->cursor = 0;
	while (rd > 0)
	{
		ft_bzero(buff, 6);
		tcsetattr(0, TCSANOW, &term->cconf);
		rd = read(fd, buff, 6);
		tcsetattr(0, TCSANOW, &term->dconf);
		if (buff[0] == '\n')
			return (1);
		if (rd > 0)
			check_char(buff, term);
	}
	return (rd);
}
