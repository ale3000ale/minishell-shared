/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:42:06 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/16 15:42:15 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error404(char *line, int pid)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split[0])
		printf("%s: command not found\n", split[0]);
	free_table(split);
	if (!pid)
		exit(127);
	return (127);
}

// some eventual free

void	quit(char *input, t_term *term)
{
	int	neg;

	close_history(&term->history);
	ft_putstr_fd("exit\n", 1);
	neg = 0;
	if (!input[0])
		exit (0);
	if (input[0] == '-' && input[1])
		neg = 1;
	if (!ft_strdigit(&input[neg]))
	{
		ft_putstr_fd(input, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(255);
	}
	exit(ft_latoi(input));
}

int	pwd(int pid, int fd[2])
{
	ft_putstr_fd(find_path(), fd[WRITE]);
	ft_putstr_fd("\n", fd[WRITE]);
	if (!pid)
		exit(0);
	return (0);
}

int	cd(char *input, int pid)
{
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
