/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 23:04:11 by zxcvbinz          #+#    #+#             */
/*   Updated: 2021/06/04 16:18:11 by amarcell         ###   ########.fr       */
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
	if (!new_path[0] || new_path[0] == '~')
		new_path = getenv("HOME");
	if (chdir(new_path) != 0)
	{
		printf("cd: %s: No such file or directory\n", new_path);
		return (1);
	}
	setenv("OLDPWD", getenv("PWD"), 1);
	setenv("PWD", find_path(), 1);
	return (0);
}
