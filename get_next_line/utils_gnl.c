/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_gnl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 17:23:22 by amarcell          #+#    #+#             */
/*   Updated: 2021/05/28 15:34:30 by amarcell         ###   ########.fr       */
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

void	cursorto(int pos, t_term *term)
{
	int	step;
	int	sign;

	sign = 1;
	step = pos - term->cursor;
	if (step < 0)
		sign = -1;
	while (step)
	{
		if (sign == -1)
			cursorbackward(term);
		else
			cursorforward(term);
		step -= sign;
	}
}

static	void	composer(char *buff, t_term *term)
{
	char	**cut;
	char	*temp;
	int		ex_pos;

	cut = ft_strcut(term->input, term->cursor);
	ex_pos = term->cursor + 1;
	cursorto(0, term);
	term->input[0] = 0;
	temp = term->input;
	term->input = ft_strjoin(temp, cut[0]);
	free(temp);
	temp = term->input;
	term->input = ft_strjoin(temp, buff);
	free(temp);
	temp = term->input;
	term->input = ft_strjoin(temp, cut[1]);
	free(temp);
	free_table(cut);
	write(1, term->input, ft_strlen(term->input));
	term->cursor = ft_strlen(term->input);
	cursorto(ex_pos, term);
}

int	echo_input(char *buff, t_term *term)
{
	char	*temp;

	if (term->cursor < (int)ft_strlen(term->input))
		composer(buff, term);
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
