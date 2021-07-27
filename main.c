/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:45:54 by dlanotte          #+#    #+#             */
/*   Updated: 2021/07/27 16:24:35 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Generate son procecess, if they are in pipe make the pipe fd and set it
// Retrurn the pid

int	son_generation(t_clist *queque)
{
	int	pp[2];
	int	pid;

	if (get_op(queque)->pipe)
	{
		if (pipe(pp) == -1)
			exit(printf("minishell: pipe fail\n") * 0 + 1);
		get_op(queque)->fd[WRITE] = pp[WRITE];
		get_op(queque->next)->fd[READ] = pp[READ];
	}
	pid = getpid();
	g_term->pid = pid;
	if (get_op(queque)->cmd[0] && (get_op(queque)->pipe \
	 || cmd_id(get_op(queque)->cmd) == -1))
	{
		pid = fork();
		g_term->pid = pid;
	}
	return (pid);
}

// Maneging the cmd request, create son process and manege it

static void	exec_file_error(t_term *term, \
	char *fd_error, int pid, int red)
{
	term->last_status = 1;
	ft_putstr_fd("minishell: ", 2);
	if (red == 1)
	{
		ft_putstr_fd(fd_error, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	if (!pid)
		exit(1);
}

static void	exec_fd_close(t_clist *queque, t_term *term, int pid)
{
	waitpid(pid, &term->last_status, 0);
	g_term->pid = getpid();
	if (get_op(queque)->fd[WRITE] > WRITE)
		close(get_op(queque)->fd[WRITE]);
	if (get_op(queque)->fd[READ] > READ)
		close(get_op(queque)->fd[READ]);
}

static void	exec_status(t_clist *queque, t_term *term)
{
	if (cmd_id(get_op(queque)->cmd) != -1 && term->last_status == 127)
		error404(get_op(queque)->cmd, 1, term);
}

void	exec_manager(t_clist *queque, t_term *term)
{
	int		pid;
	int		red;
	char	*fd_error;

	fd_error = 0;
	red = 0;
	if (get_op(queque)->red)
		red = redirection(get_op(queque), &fd_error);
	pid = son_generation(queque);
	if (get_op(queque)->cmd[0] && ((pid && !get_op(queque)->pipe \
		&& cmd_id(get_op(queque)->cmd) > -1) || (!pid)))
	{
		if (red)
			exec_file_error(term, fd_error, pid, red);
		else
			ft_execute_commands(queque, term, pid);
	}
	else
	{
		if (red && getpid() == pid)
			exec_file_error(term, fd_error, pid, red);
		exec_fd_close(queque, term, pid);
	}
	exec_status(queque, term);
}
