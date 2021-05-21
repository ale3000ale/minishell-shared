/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easy_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 11:42:06 by amarcell          #+#    #+#             */
/*   Updated: 2021/05/21 14:17:31 by amarcell         ###   ########.fr       */
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

void	quit(void)
{
	// some eventual free
	exit(0);
}
