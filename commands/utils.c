/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:36:59 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/28 17:47:24 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_id(char *cmd)
{
	char	**cmds;
	int		ret;

	cmds = ft_split(COMMANDS, ',');
	if (!ft_strncmp(cmd, cmds[MY_CD], 10))
		ret = MY_CD;
	else if (!ft_strncmp(cmd, cmds[MY_CLEAR], 10))
		ret = MY_CLEAR;
	else if (!ft_strncmp(cmd, cmds[MY_ECHO], 10))
		ret = MY_ECHO;
	else if (!ft_strncmp(cmd, cmds[MY_ENV], 10))
		ret = MY_ENV;
	else if (!ft_strncmp(cmd, cmds[MY_EXIT], 10))
		ret = MY_EXIT;
	else if (!ft_strncmp(cmd, cmds[MY_EXPORT], 10))
		ret = MY_EXPORT;
	else if (!ft_strncmp(cmd, cmds[MY_PWD], 10))
		ret = MY_PWD;
	else if (!ft_strncmp(cmd, cmds[MY_UNSET], 10))
		ret = MY_UNSET;
	else
		ret = ERROR;
	free_table(cmds);
	return (ret);
}

int	my_echo(t_op *op, int pid)
{
	int		i;
	int		n;

	i = 1;
	n = 0;
	if (op->argv[0] && !ft_strncmp(op->argv[0], "-n", 1))
	{
		n = 1;
		while (i != -1 && op->argv[0][i])
		{
			if (op->argv[0][i++] != 'n')
			{
				n = 0;
				break ;
			}
		}
	}
	i = n;
	while (op->argv[i])
	{
		if (n != i)
			ft_putstr_fd(" ", op->fd[WRITE]);
		ft_putstr_fd(op->argv[i++], op->fd[WRITE]);
	}
	if(!n)
		ft_putstr_fd("\n", 1);
	if (!pid)
		exit(0);
	return (0);
}