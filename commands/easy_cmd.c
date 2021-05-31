/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:42:06 by amarcell          #+#    #+#             */
/*   Updated: 2021/05/31 16:10:07 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error404(char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (split[0])
		printf("command not found: %s\n", split[0]);
	free_table(split);
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
