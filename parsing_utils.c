#include "includes/minishell.h"

void	double_quotes(int *iter, char *input, char **new)
{
	int		iter2;
	char	*str;
	char	*tmp;

	iter2 = *iter;
	iter2++;
	while (input[iter2] && input[iter2] != '\"')
		iter2++;
	str = ft_calloc(iter2 - *iter + 2, 1);
	str[0] = input[(*iter)++];
	iter2 = 1;
	while (input[*iter] && input[*iter] != '\"')
		str[iter2++] = input[(*iter)++];
	str[iter2] = input[*iter];
	if (input[*iter])
		(*iter)++;
	if (*new)
	{
		tmp = ft_strjoin(str, *new);
		free(*new);
		*new = tmp;
	}
	else
		*new = ft_strjoin(str, "");
	free(str);
}

static int	fucknorm2(char **str, int i, t_term *term, int fuck)
{
	char	*s;

	if (!fuck)
		return (*str[i] && *str[i] != '|' \
		 && *str[i] != '>' && *str[i] != '<' \
	 	 && *str[i] != ' ');
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
		double_quotes(iter, term->input, &new->input);
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

void	find_cmd(t_term *term, int *iter, t_op **new)
{
	int		iter2;
	char	*temp;

	if ((*new)->cmd)
		free((*new)->cmd);
	while (term->input[*iter] && term->input[*iter] == ' ')
		(*iter)++;
	iter2 = *iter;
	while (term->input[iter2] && term->input[iter2] != ' '
		&& term->input[iter2] != '>' && term->input[iter2] != '<')
		iter2++;
	(*new)->cmd = ft_calloc(iter2 + 1, 1);
	if (term->input[*iter] == '\"')
		double_quotes(iter, term->input, &(*new)->cmd);
	iter2 = ft_strlen((*new)->cmd);
	while (term->input[*iter] && term->input[*iter] != ' '
		&& term->input[*iter] != '>' && term->input[*iter] != '<')
		(*new)->cmd[iter2++] = term->input[(*iter)++];
	temp = (*new)->cmd;
	(*new)->cmd = ft_translate((*new)->cmd, term);
	free(temp);
}

void	find_cmd_input(t_term *term, int *iter, t_op **new)
{
	int	iter2;

	if ((*new)->input)
		free((*new)->input);
	if ((*new)->argv)
		free_table((*new)->argv);
	while (term->input[*iter] && term->input[*iter] == ' ')
		(*iter)++;
	iter2 = *iter;
	while (term->input[iter2] && term->input[iter2] != '|'
		&& term->input[iter2] != '>' && term->input[iter2] != '<')
		iter2++;
	(*new)->input = ft_calloc(iter2 - *iter + 2, 1);
	if (term->input[*iter] == '\"')
		double_quotes(iter, term->input, &(*new)->input);
	iter2 = ft_strlen((*new)->input);
	while (term->input[*iter] && term->input[*iter] != '|'
		&& term->input[*iter] != '>' && term->input[*iter] != '<')
		((*new)->input)[iter2++] = term->input[(*iter)++];
	iter2 = ft_strlen((*new)->input) - 1;
	while ((*new)->input[iter2] == ' ')
		(*new)->input[iter2--] = 0;
	(*new)->argv = arg_matrix((*new)->input, term);
}
