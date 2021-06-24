/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 17:45:45 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/21 19:58:35 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	red_write(t_op *op)
{
	if (op->fd[WRITE] > 1)
	{
		close(op->fd[WRITE]);
		op->fd[WRITE] = WRITE;
	}
	op->fd[WRITE] = open(op->red_write, O_RDWR | O_CREAT, 0755);
	return (1);
}

//todo gestione errori

int	red_read(t_op *op)
{
	if (op->fd[READ] > READ)
	{
		close(op->fd[READ]);
		op->fd[READ] = READ;
	}
	op->fd[READ] = open(op->red_read, O_RDONLY, 0755);
	if (op->fd[READ] < 0)
	{
		ft_putstr_fd(op->red_read, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	return (1);
}

int	red_append(t_op *op)
{
	if (op->fd[WRITE] > 1)
	{
		close(op->fd[WRITE]);
		op->fd[WRITE] = WRITE;
	}
	op->fd[WRITE] = open(op->append, O_RDWR | O_APPEND | O_CREAT, 0755);
	printf("FD: %d\n", op->fd[WRITE]);
	return (1);
}
