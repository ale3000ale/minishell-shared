/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 16:36:59 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/16 17:57:09 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	id_env(char *name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(name, env[i], ft_strlen(name)))
			return (i);
		i++;
	}
	return (-1);
}

char	*new_var(char *name, char *content)
{
	char	*var;
	char	*temp;

	var = ft_strjoin(name, "=");
	temp = var;
	var = ft_strjoin(var, content);
	free(temp);
	return (var);
}

int	ft_setenv(char *name, char *content, int option, char **env)
{
	int	ck;
	int	id;

	ck = 1;
	id = id_env(name, env);
	if (id == -1)
		mat_join_row((void **)env, new_var(name, content));
	else if (option == NONE)
		return (ck);
	else if (option == OVERWRITE)
	{
		free(env[id]);
		env[id] = new_var(name, content);
		return (ck);
	}
	else if (option == JOIN)
		return (ck);
	return (ck);
}
