#include "includes/minishell.h"

static int	fucknorm2(char **str, int i, t_term *term, int fuck)
{
	char	*s;

	if (!fuck)
		return ((*str)[i] && (*str)[i] != '|' \
		 && (*str)[i] != '>' && (*str)[i] != '<' \
	 	 && (*str)[i] != ' ');
	else
	{
		s = ft_translate(*str, term);
		free(*str);
		*str = s;
	}
	return (0);
}

void	get_red(t_term *term, int *iter, t_clist **red, int type)
{
	int		iter2;
	t_red	*new;

	new = ft_calloc(1, sizeof(t_red));
	while (term->input[*iter] == ' ')
		(*iter)++;
	iter2 = *iter;
	while (fucknorm2(&term->input, iter2, term, 0))
		iter2++;
	new->input = ft_calloc(iter2 - *iter + 2, 1);
	if (term->input[*iter] == '\"')
		quotes(iter, term->input, &new->input, '\"');
	iter2 = 0;
	while (fucknorm2(&term->input, *iter, term, 0))
		new->input[iter2++] = term->input[(*iter)++];
	while (new->input[--iter2] == ' ')
		new->input[iter2] = 0;
	fucknorm2(&new->input, 0, term, 1);
	new->type = type;
	if (*red)
		ft_clstadd_back(red, ft_clstnew(new));
	else
		*red = ft_clstnew(new);
}

int	count_row2(char *input, int *iter)
{
	int		size;
	int		flag;
	char	c;

	size = 0;
	flag = 0;
	c = input[*iter];
	while (c && ((c != ' ' && c != '>' && c != '<') || (flag % 2)))
	{
		flag += (c == '\"');
		(*iter)++;
		size++;
		c = input[*iter];
	}
	return (size);
}

void	find_cmd(t_term *term, int *iter, t_op **new)
{
	int		size;
	char	*temp;
	int		iter2;

	if ((*new)->cmd)
		free((*new)->cmd);
	while (term->input[*iter] && term->input[*iter] == ' ')
		(*iter)++;
	iter2 = *iter;
	size = count_row2(term->input, iter);
	(*new)->cmd = ft_calloc(size + 1, 1);
	ft_strlcpy((*new)->cmd, term->input + iter2, size + 1);
	temp = (*new)->cmd;
	(*new)->cmd = ft_translate((*new)->cmd, term);
	free(temp);
}

void	find_cmd_input(t_term *term, int *iter, t_op **new)
{
	int		size;
	char	*tmp;

	if ((*new)->input)
		free((*new)->input);
	if ((*new)->argv)
		free_table((*new)->argv);
	ft_skip(term->input, iter, ' ');
	size = 0;
	while (term->input[*iter + size] && term->input[*iter + size] != '|'
		&& term->input[*iter + size] != '>' && term->input[*iter + size] != '<')
		size++;
	(*new)->input = ft_calloc(size + 1, 1);
	ft_strlcpy((*new)->input, term->input + *iter, size + 1);
	*iter = *iter + size;
	tmp = (*new)->input;
	(*new)->input = ft_strtrim((*new)->input, " ");
	(*new)->argv = arg_matrix((*new)->input, term);
	free(tmp);
}
