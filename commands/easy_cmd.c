/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:42:06 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/04 14:30:16 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	error404(char *line, int pid)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split[0])
		printf("command not found: %s\n", split[0]);
	free_table(split);
	if (!pid)
		exit(127);
	return (127);
}

// some eventual free

void	quit(char *input)
{
	int	neg;

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

int	pwd(int pid)
{
	ft_putstr_fd(find_path(), 1);
	ft_putstr_fd("\n", 1);
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
