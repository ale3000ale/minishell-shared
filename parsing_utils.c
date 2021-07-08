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

void	get_red(t_term *term, int *iter, t_clist **red, int type)
{
	int	iter2;
	t_red	*new;
	char	*tmp;

	new = ft_calloc(1, sizeof(t_red));
	while (term->input[*iter] == ' ')
		(*iter)++;
	iter2 = *iter;
	while (term->input[iter2] && term->input[iter2] != '|' && term->input[iter2] != '>' && term->input[iter2] != '<' && term->input[iter2] != ' ')
		iter2++;
	new->input  = ft_calloc(iter2 - *iter + 2, 1);
	if (term->input[*iter] == '\"')
		double_quotes(iter, term->input, &new->input);
	iter2 = 0;
	while (term->input[*iter] && term->input[*iter] != '|' && term->input[*iter] != '>' && term->input[*iter] != '<' && term->input[*iter] != ' ')
		new->input[iter2++] = term->input[(*iter)++];
	iter2--;
	while (new->input[iter2] == ' ')
		new->input[iter2--] = 0;
	tmp = ft_translate(new->input, term);
	free(new->input);
	new->input = tmp;
	//printf("red input = %s\n", new->input);
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
	printf("\ncmd = %s\n", (*new)->cmd);
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
	printf("input = %s\n", (*new)->input);
	(*new)->argv  = arg_matrix((*new)->input, term);
}

void	find_red(t_term *term, int *iter, t_op **new)
{
	if (term->input[*iter] == '>' && (term->input[*iter + 1]
		&& term->input[*iter + 1] == '>'))
	{
		*iter += 2;
		get_red(term, iter, &(*new)->red, RED_APPEND);
	}
	else if (term->input[*iter] == '>')
	{
		(*iter)++;
		get_red(term, iter, &(*new)->red, RED_WRITE);
	}
	else if (term->input[*iter] == '<' && (term->input[*iter +  1]
		&& term->input[*iter + 1] == '<'))
	{
		*iter += 2;
		get_red(term, iter, &(*new)->red, RED_STDIN);
	}
	else if (term->input[*iter] == '<')
	{
		(*iter)++;
		get_red(term, iter, &(*new)->red, RED_READ);
	}
}
