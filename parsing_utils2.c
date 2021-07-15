/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:18:26 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/15 15:57:53 by amarcell         ###   ########.fr       */
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
