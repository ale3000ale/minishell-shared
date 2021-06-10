/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:57:36 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/10 19:32:48 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_history(t_term *term)
{
	char	*line;
	int		rd;

	term->history.fd = open(HISTORY, O_RDWR | O_APPEND | O_CREAT, 0755);
	if (term->history.fd < 0)
		exit(1);
	rd = get_next_line_basic(term->history.fd, &line);
	term->history.history = 0;
	if (rd > 0)
		term->history.history = ft_clstnew(line);
	while (rd > 0)
	{
		rd = get_next_line_basic(term->history.fd, &line);
		if (!rd)
			continue ;
		ft_clstadd_front(term->history.history, ft_clstnew(line));
	}
	free(line);
	if (rd < 0)
		ft_clstclear(term->history.history, free);
	term->history.count_new = 0;
	// close(term->history.fd);
}

void	append_history(t_history *history, char *line)
{
	t_clist	*new;

	history->history = ft_clstlast(history->history)->next;
	new = ft_clstnew(line);
	ft_clstadd_front(&history->history, new);
}

char	*get_history(int dir, t_history *history)
{
	if (dir == PREC && !history->history->next->last)
		history->history = history->history->next;
	else if (dir == NEXT && !history->history->pre->last)
		history->history = history->history->pre;
	return ((char *)history->history->content);
}

void	history_change(t_history *history, char *line)
{
	free(history->history->content);
	history->history->content = ft_join("", line);
}

void	close_history(t_history *history)	//salva dallúltimo al primo
{
	history->history = ft_clstlast(history);
	while (history->history && history->count_new > 0)
	{
		ft_putstr_fd((char *)history->history->content, history->fd);
		ft_putstr_fd("\n", history->fd);
		history->count_new--;
		history->history = history->history->next;
	}
	free_table(history->history);
	close(history->fd);
}
