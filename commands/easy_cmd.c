/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:42:06 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/21 17:38:09 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error404(char *line, int pid, t_term *term)
{
	char	*tmp;

	if (line)
	{
		printf("error = %d\n", term->last_status);
		tmp = ft_translate(line, term);
		printf("%s: command not found\n", tmp);
		free(tmp);
	}
	if (!pid)
		exit(127);
	return (127);
}

// some eventual free

void	quit(char *input, t_term *term)
{
	int		neg;

	input = ft_translate(input, term);
	close_history(&term->history);
	ft_putstr_fd("exit\n", 1);
	neg = 0;
	if (!input[0])
	{
		free(input);
		exit (0);
	}
	if (input[0] == '-' && input[1])
		neg = 1;
	if (!ft_strdigit(&input[neg]))
	{
		ft_putstr_fd(input, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		free(input);
		exit(255);
	}
	neg = ft_latoi(input);
	free(input);
	exit(neg);
}

int	pwd(int pid, int fd[2])
{
	ft_putstr_fd(find_path(), fd[WRITE]);
	ft_putstr_fd("\n", fd[WRITE]);
	if (!pid)
		exit(0);
	return (0);
}

int	cd(char *input, int pid, t_term *term)
{
	input = ft_translate(input, term);
	change_path(input);
	if (!pid)
		exit(0);
	return (0);
}

int	clear_cmd(int pid)
{
	my_clear_screen();
	if (!pid)
		exit(0);
	return (0);
}
