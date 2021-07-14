/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:02:58 by dlanotte          #+#    #+#             */
/*   Updated: 2021/07/14 16:10:57 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
//todo: togliere spazi fine stringa
//		matrice degli argomenti in t_op

// convert void* in a list to t_op *  and return it
t_op	*get_op(t_clist *cls)
{
	return ((t_op *)cls->content);
}

// create a cmd node and fill it
// and add back cmd node, split each cmd whith '|'

void	free_red(void *red)
{
	t_red	*tmp;

	tmp = (t_red *)red;
	if (tmp->input)
	{
		free(tmp->input);
		tmp->input = 0;
	}
	free(tmp);
	tmp = 0;
}

void	free_op(void *op)
{
	t_op	*tmp;

	tmp = (t_op *)op;
	if (tmp->cmd)
		free(tmp->cmd);	
	if ((tmp)->input)
		free((tmp)->input);
	if (tmp->argv)
		free_table(tmp->argv);
	if (tmp->red)
		ft_clstclear(&tmp->red, free_red);
	tmp->cmd = 0;
	tmp->input = 0;
	tmp->argv = 0;
	tmp->red = 0;
	free(op);
	op = 0;
}

void	new_node(t_term *term, int *iter, t_op **new)
{
	(*new)->fd[WRITE] = WRITE;
	(*new)->oldfd[WRITE] = WRITE;
	(*new)->fd[READ] = READ;
	(*new)->oldfd[READ] = READ;
	if (term->input[*iter] == '|')
	{
		(*new)->pipe = 1;
		ft_clstadd_back(&(term->queque.first), ft_clstnew(*new));
		if (term->input[*iter + 1])
			(*iter)++;
		while (term->input[*iter] && term->input[*iter] == ' ')
			(*iter)++;
		*new = ft_calloc(1, sizeof(t_op));
	}
	else if (!term->input[*iter])
		ft_clstadd_back(&(term->queque.first), ft_clstnew(*new));
}

static void	parse_cmd(t_term *term)
{
	int		iter;
	int		iter2;
	t_op	*new;

	iter = 0;
	while (term->input[iter] == ' ')
		iter++;
	iter2 = iter;
	new = ft_calloc(1, sizeof(t_op));
	while (term->input[iter])
	{
		// find cmd
		if (!new->cmd || !(new->cmd)[0])
			find_cmd(term, &iter, &new);
		// find cmd input
		find_cmd_input(term, &iter, &new);
		// if there are redirectiono
		while (term->input[iter] && term->input[iter] != '|' && term->input[iter] != ' ')
			find_red(term, &iter, &new);
				//check if there are pipes or is end of string
		if (!term->input[iter] || term->input[iter] == '|')
			new_node(term, &iter, &new);
	}
}

int	ft_parsing_hub(t_term *term)
{
	int		ex;
	t_clist	*cmds;

	ex = 0;
	term->queque.first = 0;
	if (term->input[0])
	{
		parse_cmd(term);
		cmds = term->queque.first;
		write(1, "\n", 1);
		printf("\033[0m\033[0;37m");
		while (!ex && cmds)
		{
			exec_manager(cmds, term);
			ex = cmds->last;
			cmds = cmds->next;
		}
		ft_clstclear(&term->queque.first, free_op);
		free(term->input);
	}
	else
		ft_putstr_fd("\n", 1);
	return (1);
}
