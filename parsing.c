/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:02:58 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/24 12:20:32 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"
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

char	*double_quotes(int *iter, char *input)
{
	int		iter2;
	char	*str;

	iter2 = *iter;
	iter2++;
	while (input[iter2] != '\"')
		iter2++;
	str = ft_calloc(iter2 - *iter + 2, 1);
	str[0] = input[*iter];
	(*iter)++;
	iter2 = 1;
	while (input[*iter] != '\"')
		str[iter2++] = input[(*iter)++];
	str[iter2] = input[*iter];
	(*iter)++;
	return (str);
}

void	get_red(char *input, int *iter, char **str)
{
	int	iter2;

	while (input[*iter] == ' ')
		(*iter)++;
	iter2 = *iter;
	while (input[iter2] && input[iter2] != '|')
		iter2++;
	*str = ft_calloc(iter2 - *iter + 2, 1);
	if (input[*iter] == '\"')
		*str = ft_strjoin(*str, double_quotes(iter, input));
	iter2 = 0;
	while (input[*iter] && input[*iter] != '|')
		(*str)[iter2++] = input[(*iter)++];
}

void	free_op(void *op)
{
	t_op	*tmp;

	tmp = (t_op *)op;
	if (tmp->cmd)
		free(tmp->cmd);	
	if ((tmp)->input)
		free((tmp)->input);
	if ((tmp)->append)
		free((tmp)->append);
	if ((tmp)->red_read)
		free((tmp)->red_read);
	if ((tmp)->red_stdin)
		free((tmp)->red_stdin);
	if ((tmp)->red_write)
		free((tmp)->red_write);
	free(tmp);
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
	while (term->input[iter])
	{
		new = ft_calloc(1, sizeof(t_op));
		// find cmd
		while (term->input[iter2] && term->input[iter2] != ' ')
			iter2++;
		new->cmd = calloc(iter2 + 1, 1);
		if (term->input[iter] == '\"')
			new->cmd = ft_strjoin(new->cmd, double_quotes(&iter, term->input));
		iter2 = ft_strlen(new->cmd);
		while (term->input[iter] && term->input[iter] != ' ')
			new->cmd[iter2++] = term->input[iter++];
		new->cmd = ft_translate(new->cmd, term);
		printf("\ncmd = %s\n", new->cmd);
		// find cmd input
		while (term->input[iter] && term->input[iter] == ' ')
			iter++;
		iter2 = iter;
		while (term->input[iter2] && term->input[iter2] != '|'
			&& term->input[iter2] != '>' && term->input[iter2] != '<')
			iter2++;
		new->input = ft_calloc(iter2 - iter + 2, 1);
		if (term->input[iter] == '\"')
			new->input = ft_strjoin(new->input, double_quotes(&iter, term->input));
		iter2 = ft_strlen(new->input);
		while (term->input[iter] && term->input[iter] != '|'
			&& term->input[iter] != '>' && term->input[iter] != '<')
			(new->input)[iter2++] = term->input[iter++];
		printf("input = %s\n", new->input);
		// if there are redirection
		if (term->input[iter] == '>' && (term->input[iter + 1] && term->input[iter + 1] == '>'))
		{
			iter += 2;
			get_red(term->input, &iter, &new->append);
			printf("append = %s\n", new->append);
		}
		else if (term->input[iter] == '>')
		{
			iter++;
			get_red(term->input, &iter, &new->red_write);
			printf("red_write = %s\n", new->red_write);
		}
		else if (term->input[iter] == '<' && (term->input[iter +  1] && term->input[iter + 1] == '<'))
		{
			iter += 2;
			get_red(term->input, &iter, &new->red_stdin);
			printf("red_stdin = %s\n", new->red_stdin);
		}
		else if (term->input[iter] == '<')
		{
			iter++;
			get_red(term->input, &iter, &new->red_read);
			printf("red_read = %s\n", new->red_read);
		}
		//set fd
		new->fd[WRITE] = WRITE;
		new->oldfd[WRITE] = WRITE;
		new->fd[READ] = READ;
		new->oldfd[READ] = READ;
		//check if there are pipes or is end of string
		if (term->input[iter] == '|')
		{
			new->pipe = 1;
			ft_clstadd_back(&(term->queque.first), ft_clstnew(new));
			if (term->input[iter + 1])
				iter++;
			while (term->input[iter] && term->input[iter] == ' ')
				iter++;
		}
		else if (!term->input[iter])
		{
			ft_clstadd_back(&(term->queque.first), ft_clstnew(new));
		}
	}
	printf("fine\n");
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
		while (!ex && cmds)
		{
			exec_manager(cmds, term);
			ex = cmds->last;
			cmds = cmds->next;
		}
		ft_clstclear(&term->queque.first, free_op);
		/*term->queque.first = 0;
		cmds = 0;
		printf("\nQUEQUE p: %p cmd: %s in: %s  next: %p\n", \
			term->queque.first, get_op(term->queque.first)->cmd, get_op(term->queque.first)->input, \
			term->queque.first->next);*/
	}
	write(1, "\n", 1);
	return (1);
}
