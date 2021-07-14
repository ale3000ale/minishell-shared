/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:45:45 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/14 15:38:52 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	red_stdin(t_op *op, t_red *tmp)
{
	char	*line;
	int		pp[2];

	if (op->fd[READ] > READ)
		close (op->fd[READ]);
	if (pipe(pp) == -1)
		return (1);
	op->fd[READ] = pp[READ];
	ft_putstr_fd(">", 1);
	line = 0;
	while (get_next_line_basic(0, &line) != -1 \
	 && ft_strncmp(line, tmp->input, ft_strlen(tmp->input) + 1))
	{
		ft_putstr_fd(line, pp[WRITE]);
		ft_putstr_fd("\n", pp[WRITE]);
		ft_putstr_fd(">", 1);
		free(line);
		line = 0;
	}
	close(pp[WRITE]);
	if (!line)
		return (1);
	free(line);
	line = 0;
	return (0);
}

static int	red_support(t_op *op, t_red *tmp)
{
	if (tmp->type == RED_WRITE || tmp->type == RED_APPEND)
	{
		if (op->fd[WRITE] > 1)
			close(op->fd[WRITE]);
		if (tmp->type == RED_WRITE)
			op->fd[WRITE] = open(tmp->input, O_RDWR | O_TRUNC | O_CREAT, 0755);
		else
			op->fd[WRITE] = open(tmp->input, O_RDWR | O_APPEND | O_CREAT, 0755);
		if (op->fd[WRITE] < 0)
			return (1);
	}
	else if (tmp->type == RED_READ)
	{
		if (op->fd[READ] > 0)
			close(op->fd[READ]);
		op->fd[READ] = open(tmp->input, O_RDONLY, 0444);
		if (op->fd[READ] < 0)
			return (1);
	}
	else if (tmp->type == RED_STDIN)
		return (red_stdin(op, tmp));
	return (0);
}

int	redirection(t_op *op, char **fd_error)
{
	t_red	*tmp;
	int		ex;

	ex = 0;
	while (!ex)
	{
		tmp = (t_red *)op->red->content;
		if (red_support(op, tmp))
		{
			*fd_error = ft_strjoin("", tmp->input);
			return (-1);
		}
		ex = op->red->last;
		op->red = op->red->next;
	}
	return (0);
}
