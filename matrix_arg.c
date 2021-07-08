#include "includes/minishell.h"
#include "includes/my_main_functions.h"

void	alloc_matrix(char ***matrix, char *input)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (input[i])
	{
		if (input[i] == ' ')
			size++;
		if (input[i] == '\"')
		{
			size++;
			i++;
			while (input[i] && input[i] != '\"')
				i++;
		}
		if (input[i])
			i++;
	}
	*matrix = ft_calloc(size + 2, sizeof(char *));;
}

char	*get_to_trans(int *iter, char *input)
{
	int	tmp;
	char	*str;

	if (input[*iter] == ' ')
		(*iter)++;
	tmp = *iter;
	while (input[*iter] && input[*iter] != ' ')
		(*iter)++;
	str = ft_calloc(*iter - tmp + 1, 1);
	ft_memcpy(str, input + tmp, *iter - tmp);
	return (str);
}

char	**arg_matrix(char *input, t_term *term)
{
	char	**matrix;
	int	i;
	int	iter;
	char	*to_trans;

	alloc_matrix(&matrix, input);
	iter = 0;
	i = 0;
	to_trans = 0;
	while (input[iter])
	{
		if (input[iter] == '\"')
		{
			double_quotes(&iter, input, &to_trans);
			matrix[i++] = ft_translate(to_trans, term);
			free(to_trans);
		}
		else
		{	
			to_trans = get_to_trans(&iter, input);
			matrix[i++] = ft_translate(to_trans, term);
			free(to_trans);
			iter++;
		}
	}
	return (matrix);
}
