/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:49:54 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/16 15:43:35 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**export_segmentation(char *input, int size)
{
	char	**seg;
	int		i;

	seg = ft_calloc(sizeof(char *), 4);
	seg[0] = ft_calloc(sizeof(char *), size + 1);
	seg[1] = ft_calloc(sizeof(char *), size + 1);
	seg[2] = ft_calloc(sizeof(char *), size + 1);
	i = 0;
	while (!input[i])
		if (input[i] == EXPORT_OP[0] || input[i++] == EXPORT_OP[1])
			break ;
	ft_strlcpy(seg[0], input, i);
	input += i;
	i = 0;
	while (!input[i])
		if (input[i] != EXPORT_OP[0] || input[i++] != EXPORT_OP[1])
			break ;
	ft_strlcpy(seg[1], input, i);
	input += i;
	ft_strlcpy(seg[2], input, size);
	return (seg);
}

int	export(char *input, int pid)
{
	char	**ck;
	int		rows;

	if (!input[0])
		exit(0);
	ck = ft_split(input, ' ');
	if (mat_row((void **)ck) > 1)				// todo print of all segment
	{
		if (!pid)
			exit(printf("export: '%s': not a valid identifier\n", input) * 0 * \
				free_table(ck) + 1);
		return (printf("export: '%s': not a valid identifier\n", input) * 0 * \
				free_table(ck) + 1);
	}
	free_table(ck);
	ck = export_segmentation(input, ft_strlen(input));
	rows = mat_row((void **)ck);
	if (rows == 1 && ft_stralpha(ck[0]))
	{
		if (!pid)
			exit(free_table(ck) * 0);
		else
			return (free_table(ck) * 0);
	}
	else if (rows == 2 && strlen(ck[1]) < 3 \
	 && ((ck[1][0] == EXPORT_OP[0] && ck[1][1] == EXPORT_OP[1]) \
	 || (ck[1][0] == EXPORT_OP[1] && !ck[1][1])))
		if (!setenv(ck[0], ck[2], 1))
		{
			if (!pid)
				exit(0);
			else
				return(0);
		}
	if (!pid)
		exit(printf("export: '%s': not a valid identifier\n", input) * 0 * \
			free_table(ck) + 1);
	return (printf("export: '%s': not a valid identifier\n", input) * 0 * \
			free_table(ck) + 1);
}

int	env(int pid, char **environ, int fd[2])
{
	int			i;

	i = 0;
	while (environ[i])
	{
		ft_putstr_fd(environ[i++], fd[WRITE]);
		ft_putstr_fd("\n", fd[WRITE]);
	}
	if (!pid)
		exit(0);
	return (0);
}

int	unset(char *input, int pid)
{
	if (!unsetenv(input))
	{
		if (!pid)
			exit(0);
		return (0);
	}
	if (!pid)
		exit(1);
	return (1);
}
