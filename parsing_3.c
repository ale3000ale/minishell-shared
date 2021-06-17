/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mobrycki <mobrycki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 12:33:21 by mobrycki          #+#    #+#             */
/*   Updated: 2021/06/17 15:52:24 by mobrycki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	if1(char **input, char **trans, int *iter)
{
	int	flag;

	flag = 0;
	if (**input == '\\')
	{
		(*input)++;
		(*trans)[(*iter)++] = **input;
		(*input)++;
		flag = 1;
	}
	else if (**input == 39)
	{
		(*input)++;
		while (**input && **input != 39)
		{
			(*trans)[(*iter)++] = **input;
			(*input)++;
		}
		if (**input)
			(*input)++;
		flag = 1;
	}
	return (flag);
}

void	if2(char **input, char **trans, int *iter, char **env)
{
	if (**input == '\"')
	{
		(*input)++;
		while (**input && **input != '\"')
		{
			if (**input == '$')
				*trans = ft_dollar(input, env, trans, iter);
			else
			{
				(*trans)[(*iter)++] = **input;
				(*input)++;
			}
		}
		if (**input)
			(*input)++;
	}
	else if (**input == '$')
		*trans = ft_dollar(input, env, trans, iter);
	else if (**input)
	{
		(*trans)[(*iter)++] = **input;
		(*input)++;
	}
}

char	*ft_translate(char *input, char **env)
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
			if2(&input, &trans, &iter, env);
	}
	trans[iter] = 0;
	return (trans);
}
