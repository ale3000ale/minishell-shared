/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:12:51 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/10 15:12:34 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create a second process where it execute shell base command like ls
//		we need 2 proces because execve substitute the current process with 
//		called proces

int	exec_cmd(char *cmd, char *input, int pid)
{
	int		ret;
	char	**args;

	if (pid)
		pid = fork();
	if (!pid)
	{
		input = ft_strjoin(cmd, input);
		args = ft_split(input, ' ');
		cmd = ft_strjoin(BIN, cmd);
		if (execve(cmd, args, NULL) == -1)
		{
			free_table(args);
			free(cmd);
			free(input);
			exit(127);
		}
	}
	wait(&ret);
	printf("ret: %d\n",ret >> 8);
	return (ret);
}
