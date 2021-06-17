/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:02:58 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/16 16:18:01 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// convert void* in a list to t_op *  and return it
t_op	*get_op(t_clist *cls)
{
	return ((t_op *)cls->content);
}

// create a cmd node and fill it

static t_clist	*make_cmd(char *input, int pipe)
{
	char	**string_parsing;
	t_clist	*new;

	string_parsing = ft_split(input, ' ');
	new = ft_clstnew((t_op *)malloc(sizeof(t_op)));
	get_op(new)->cmd = ft_strdup(string_parsing[0]);
	get_op(new)->input = \
		ft_strdup(&input[ft_strlen(string_parsing[0]) + 1]);
	free_table(string_parsing);
	get_op(new)->fd[WRITE] = WRITE;
	get_op(new)->fd[READ] = READ;
	get_op(new)->pipe = pipe;
	get_op(new)->error = 0;
	return (new);
}

// and add back cmd node, split each cmd whith '|'

static void	parse_cmd(t_term *term)
{
	char	**cmds;
	int		i;
	int		size;

	i = -1;
	cmds = ft_split(term->input, '|');
	size = mat_row((void **)cmds);
	while (cmds[++i])
		ft_clstadd_back(&term->queque.first, make_cmd(cmds[i], i < size - 1));
	free_table(cmds);
}

// free struct t_op

void	free_op(void *operation)
{
	t_op	*op;

	op = (t_op *)operation;
	free(op->input);
	free(op->cmd);
}

//	make the cmd queque and execute the command 

int	ft_parsing_hub(t_term *term)
{
	int		ex;
	t_clist	*cmds;

	//printf("\nline |%s|\n", term->input);
	ex = 0;
	term->queque.first = 0;
	if (term->input[0])
	{
		parse_cmd(term);
		cmds = term->queque.first;
		write(1, "\n", 1);
		printf("\033[0m\033[0;37m");
		while (!ex)
		{
			exec_manager(cmds, term);
			ex = cmds->last;
			cmds = cmds->next;
		}
		ft_clstclear(&term->queque.first, free_op);
		term->queque.first = 0;
		cmds = 0;
		/*printf("\nQUEQUE p: %p cmd: %s in: %s  next: %p\n", \
			term->queque.first, get_op(term->queque.first)->cmd, get_op(term->queque.first)->input, \
			term->queque.first->next);*/
	}
	return (1);
}
