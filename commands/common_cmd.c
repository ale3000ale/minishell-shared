/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 15:12:51 by amarcell          #+#    #+#             */
/*   Updated: 2021/07/12 17:46:27 by amarcell         ###   ########.fr       */
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

int	exec_cmd(t_op *op, int pid, char **env)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_calloc(mat_row((void **)op->argv) + 2, sizeof(char *));
	if (op->cmd)
		args[i] = op->cmd;
	while (op->argv[i])
	{
		args[i + 1] = op->argv[i];
		i++;
	}
	if (!pid)
	{
		son_exe(op->cmd, args, env);
		if (execve(op->cmd, args, env) == -1)
		{
			free_table(args);
			printf("minishell: %s: command not found\n", op->cmd);
			exit(127);
		}
	}
	return (1);
}
