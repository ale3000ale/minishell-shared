/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 15:57:36 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/12 16:28:08 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_history(t_term *term)
{
	char	*line;
	int		rd;

	line = 0;
	term->history.fd = open(HISTORY, O_RDWR | O_APPEND | O_CREAT, 0755);
	if (term->history.fd < 0)
		exit(1);
	rd = get_next_line_basic(term->history.fd, &line);
	term->history.history = 0;
	if (rd > 0 && line)
		ft_clstadd_front(&term->history.history, ft_clstnew(line));
	while (rd > 0)
	{
		rd = get_next_line_basic(term->history.fd, &line);
		if (!rd)
			continue ;
		ft_clstadd_front(&term->history.history, ft_clstnew(line));
	}
	if (line)
		free(line);
	if (rd < 0)
		ft_clstclear(&term->history.history, free);
	ft_clstadd_front(&term->history.history, ft_clstnew(ft_strjoin("", "")));
	term->history.count_new = 0;
}

void	history_change(t_history *history, char *line)
{
	free(history->history->content);
	history->history->content = line;
	//printf("change finish |%s| %p\n", (char*)history->history->content, history->history);
}

int	append_history(t_history *history, char *line)
{
	t_clist	*new;

	history->history = ft_clstlast(history->history)->next;
	free(history->history->content);
	history->history->content = ft_strjoin(line, "");
	new = ft_clstnew(ft_strjoin("", ""));
	ft_clstadd_front(&history->history, new);
	history->count_new++;
	return (1);
}

char	*get_history(int dir, t_history *history)
{
	if (dir == PREC && !history->history->last)
		history->history = history->history->next;
	else if (dir == NEXT && !history->history->pre->last)
		history->history = history->history->pre;
	return ((char *)history->history->content);
}

void	close_history(t_history *history)
{
	int	i;

	i = history->count_new;
	history->history = ft_clstlast(history->history)->next->next;
	while (history->history && i > 1)
	{
		history->history = history->history->next;
		/*printf("exixXx i %d n %d |%s| %p\n",i, history->count_new, \
			(char*)history->history->content, history->history);*/
		i--;
	}
	while (history->history && history->count_new > 0)
	{
		ft_putstr_fd((char *)history->history->content, history->fd);
		ft_putstr_fd("\n", history->fd);
		/*printf("exixXx n %d |%s| %p\n", history->count_new, \
			(char*)history->history->content, history->history);*/
		history->count_new--;
		history->history = history->history->pre;
	}
	close(history->fd);
}
