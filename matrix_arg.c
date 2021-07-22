/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 18:33:31 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/22 20:23:10 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/my_main_functions.h"
#include <stdio.h>

/*int	count_row(char *input, int *iter)
{
	int	size;

	printf("input count = %s\n", input);
	size = 0;
	while (input[*iter] && input[*iter] != ' ')
	{
		if (input[*iter] == '\"')
		{
			(*iter)++;
			size++;
			while (input[*iter] && input[(*iter)++] != '\"')
				size++;
			(*iter)++;
			size++;
		}
		if (input[*iter] && input[*iter] != ' ' && input[*iter] != '\"')
		{
			(*iter)++;
			size++;
		}
	}
	return (size);
}*/

int	count_row(char *input, int *iter)
{
	int	size;
	int	flag;

	//printf("input count = %s\n", input);
	size = 0;
	flag = 0;
	while (input[*iter] && (input[*iter] != ' ' || (flag % 2)))
	{
		flag += (input[*iter] == '\"');
		(*iter)++;
		size++;
	}
	return (size);
}

/* void	split_input(char *input, t_term *term, char ***split)
{
	int	iter;
	int	i;
	int	iter2;
	int	size;
	char	*tmp;
	t_term *a;
	tmp = 0;
	iter = 0;
	iter2 = 0;
	i = 0;
	size = 0;
	a = term;
	while (input[iter])
	{
		iter2 = iter;
		//printf("INPUT = |%s|\n", input);
		size = count_row(input, &iter);
		if ((input[iter] && input[iter] == ' ') || !input[iter])
		{
			tmp = ft_calloc(size + 2, 1);
			ft_strlcpy(tmp, &input[iter2], iter - iter2 + 1);
			(*split)[i] = ft_translate(tmp, term);
			//printf("split[%d] = |%s| in: |%s|\n",i, (*split)[i], input);
			i++;
			free(tmp);
			while (input[iter] && input[iter] == ' ')
				iter++;
		}
	}
	(*split)[i] = 0;
} */

void	split_input(char *input, t_term *term, char ***split)
{
	int		iter;
	int		size;
	int		i;
	char	*tmp;
	int		iter2;

	iter = 0;
	i = 0;
	while (input[iter])
	{
		iter2 = iter;
		size = count_row(input, &iter);
		if (size)
		{
			tmp = ft_calloc(size + 1, 1);
			ft_strlcpy(tmp, &input[iter2], size + 1);
			//printf("tmp = %s\n", tmp);
			(*split)[i++] = ft_translate(tmp, term);
			//printf("\nsplit[%d] = |%s|\n", i, (*split)[i]);
			free(tmp);
		}
		while (input[iter] == ' ')
			iter++;
	}
	(*split)[i] = 0;
}

char	**arg_matrix(char *input, t_term *term)
{
	char	**matrix;
	int		count;
	int		iter;

	count = 0;
	iter = 0;
	//printf("\ninput = %s\n", input);
	while (input[iter])
	{
		if (count_row(input, &iter))
			count++;
		while (input[iter] == ' ')
			iter++;
	}
	matrix = ft_calloc(count + 1, sizeof(char *));
	split_input(input, term, &matrix);
	//printf("matrix 1 = %s\n", matrix[1]);
	return (matrix);
}

/* char	**arg_matrix(char *input, t_term *term)
{
	char	**matrix;
	int	count;
	int	iter;

	count = 0;
	iter = 0;
	//printf("\ninput = %s\n", input);
	while (input[iter])
	{
		if (input[iter] == '\"')
		{
			iter++;
			while (input[iter] && input[iter] != '\"')
				iter++;
			iter++;
		}
		if (input[iter] == ' ')
		{
			count++;
			while (input[iter] == ' ')
				iter++;
		}
		if (input[iter])
			iter++;
	}
	matrix = ft_calloc(count + 2, sizeof(char *));
	split_input(input, term, &matrix);
	//printf("matrix 1 = %s\n", matrix[1]);
	return (matrix);
} */
