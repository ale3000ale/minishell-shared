/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zxcvbinz <zxcvbinz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:23:22 by amarcell          #+#    #+#             */
/*   Updated: 2021/05/26 19:49:46 by zxcvbinz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cursorforward(t_term *term)
{
	//printf("pos: %d len: %lu\n",term->cursor, ft_strlen(term->input));
	if ((term->cursor < (int)ft_strlen(term->input)))
	{
		write(1, "\033[1C", 4);
		term->cursor++;
	}
	return (1);
}

int	cursorbackward(t_term *term)
{
	if ((term->cursor > 0))
	{
		write(1, "\033[1D", 4);
		term->cursor--;
	}
	return (1);
}

int	echo_input(char *buff, t_term *term)
{
	char	*temp;

	if (term->cursor < (int)ft_strlen(term->input))
	{
		//when cursor is inside of the string trim it and put he char
	}
	else
	{
		term->cursor++;
		temp = term->input;
		term->input = ft_strjoin(temp, buff);
		free(temp);
		write(1, buff, ft_strlen(buff));
	}
	return (2);
}
