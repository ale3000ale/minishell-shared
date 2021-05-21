/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zxcvbinz <zxcvbinz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:04:11 by zxcvbinz          #+#    #+#             */
/*   Updated: 2021/05/21 23:16:51 by zxcvbinz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(void)
{
	char	*current_path;
	char	*buf;

	buf = malloc((size_t) PATH_MAX + 1);
	if (buf)
		current_path = getcwd(buf, PATH_MAX + 1);
	else
		return (NULL);
	free(buf);
	return (current_path);
}

int	change_path(char *new_path)
{
	if (chdir(new_path) != 0)
	{
		printf("cd: no such file or directory: %s\n", new_path);
		return (0);
	}
	return (1);
}
