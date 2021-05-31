/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:49:54 by amarcell          #+#    #+#             */
/*   Updated: 2021/05/31 19:25:17 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	export(char *input)
{
	char	*name;
	char	*value;
	int		i;

	i = ft_strchrid(input, '=');
	if (i < ft_strchrid(input, ' ') || ft_strchrid(input, ' ') == -1)
	{
		if (!input[i + 1])
			return ;
		name = ft_calloc(i + 2, 1);
		ft_strlcpy(name, input, i + 1);
		input += i + 1;
		// todo parsing " and '
		value = ft_calloc(strlen(input), 1);
		ft_strlcpy(value, input, strlen(input));
		setenv(name, value, 1);
	}
}

void	env(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		ft_putstr_fd(environ[i++], 1);
		ft_putstr_fd("\n", 1);
	}
}

void	unset(char *input)
{
	unsetenv(input);
}
