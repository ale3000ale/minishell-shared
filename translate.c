/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:33:21 by mobrycki          #+#    #+#             */
/*   Updated: 2021/07/15 17:10:24 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	if1(char **input, char **trans, int *iter)
{
	int	flag;
	int	quotes;
	int	i;

	i = -1;
	quotes = 0;
	flag = (**input == 39);
	if (flag)
	{
		(*input)++;
		while ((*input)[++i] && !quotes)
			quotes = (quotes || ((*input)[i] == '\''));
		if (quotes)
		{
			while (**input && **input != 39)
			{
				(*trans)[(*iter)++] = **input;
				(*input)++;
			}
			(*input) = *input + (**input != 0);
		}
		else
			(*trans)[(*iter)++] = '\'';
	}
	return (flag);
}

static void	ifuck2(char **input, char **trans, int *iter, t_term *term)
{
	while (**input && **input != '\"')
	{
		if (**input == '$')
			ft_dollar(input, term, trans, iter);
		else
		{
			(*trans)[(*iter)++] = **input;
			(*input)++;
		}
	}
	if (**input)
		(*input)++;
}

//search for double quotes and dollars, else just copy the char in trans
void	if2(char **input, char **trans, int *iter, t_term *term)
{
	int	i;
	int	quotes;

	quotes = 0;
	i = -1;
	if (**input == '\"')
	{
		(*input)++;
		while ((*input)[++i] && !quotes)
			if ((*input)[i] == '\"')
				quotes = 1;
		if (quotes)
			ifuck2(input, trans, iter, term);
		else
			(*trans)[(*iter)++] = '\"';
	}
	else if (**input == '$')
		ft_dollar(input, term, trans, iter);
	else if (**input)
	{
		(*trans)[(*iter)++] = **input;
		(*input)++;
	}
}

//look over the string for special char and translate them
char	*ft_translate(char *input, t_term *term)
{
	char	*trans;
	int		iter;	

	iter = 0;
	trans = malloc(ft_strlen(input));
	ft_bzero(trans, ft_strlen(input));
	while (*input)
	{
		if (*input == ' ')
		{
			trans[iter++] = *input;
			while (*input && *input == ' ')
				input++;
		}
		if (!if1(&input, &trans, &iter))
			if2(&input, &trans, &iter, term);
	}
	trans[iter] = 0;
	return (trans);
}
