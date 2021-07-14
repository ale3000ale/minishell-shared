/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcarbone <gcarbone@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 16:29:17 by gcarbone          #+#    #+#             */
/*   Updated: 2021/07/14 16:34:56 by gcarbone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	id_env(char *name, char **env)
{
	int		i;
	char	**spl;

	i = 0;
	while (env[i])
	{
		spl = ft_split(env[i], '=');
		if (!ft_strcmp(name, spl[0]))
		{
			free_table(spl);
			return (i);
		}
		free_table(spl);
		i++;
	}
	return (-1);
}
