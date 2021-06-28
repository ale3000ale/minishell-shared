/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:12:51 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/28 18:54:34 by alexmarcell      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// Create a second process where it execute shell base command like ls
//		we need 2 proces because execve substitute the current process with 
//		called proces

static void	son_exe(char *cmd, char **args, char **env)
{
	int		i;
	char	*temp;
	char	**path;

	path = ft_split(getenv("PATH"), ':');
	i = 0;
	while (path[i])
	{
		temp = path[i];
		path[i] = ft_strjoin(path[i], "/");
		free(temp);
		temp = ft_strjoin(path[i], cmd);
		execve(temp, args, env);
		free(temp);
		i++;
	}
	free_table(path);
}

int	exec_cmd(char *cmd, char *input, int pid, char **env)
{
	char	**args;
	char	*temp;

	if (!pid)
	{
		input = ft_strjoin(" ", input);
		temp = input;
		input = ft_strjoin(cmd, input);
		free(temp);
		args = ft_split(input, ' ');
		son_exe(cmd, args, env);
		if (execve(cmd, args, env) == -1)
		{
			free_table(args);
			args = 0;
			free(cmd);
			cmd = 0;
			free(input);
			input = 0;
			exit(127);
		}
	}
	return (1);
}
