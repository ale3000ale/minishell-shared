/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:36:59 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/09 18:44:21 by amarcell         ###   ########.fr       */
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
