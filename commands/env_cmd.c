/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:49:54 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/18 19:31:12 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	strck(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!(ft_isalnum(s[i]) || s[i] != '_'))
			return (0);
		i++;
	}
	return (1);
}

static char	**export_segmentation(char *input)
{
	char	**cut;
	int		plus;
	int		len;
	char	**ret;

	ret = ft_calloc(3, sizeof(char *));
	if (ft_strchrid(input, '=') != -1)
	{
		cut = ft_strcut(input, ft_strchrid(input, '=') + 1);
		ret[1] = ft_strdup(cut[1]);
		plus = (cut[0][ft_strchrid(input, '=') - 1] == '+');
		len = ft_strlen(cut[0]) - plus;
		free_table(cut);
		cut = ft_strcut(input, len - 1);
		ret[0] = ft_strdup(cut[0]);
		free_table(cut);
	}
	else
	{
		ret[0] = ft_strdup(input);
		ret[1] = ft_strdup("");
	}
	return (ret);
}

static int	ck_input(char *input)
{
	char	**cut;
	int		plus;
	int		len;
	int		equal;

	equal = ft_strchrid(input, '=');
	if (equal != -1)
	{
		cut = ft_strcut(input, ft_strchrid(input, '='));
		plus = (cut[0][ft_strchrid(input, '=') - 1] == '+');
		len = ft_strlen(cut[0]) - plus - 1;
		if (len && ft_isalpha(cut[0][0]))
		{
			free_table(cut);
			cut = ft_strcut(input, len - 1);
			len = strck(&cut[0][1]);
			free_table(cut);
			return (len);
		}
		free_table(cut);
		return (0);
	}
	return (ft_isalpha(input[0]) && strck(&input[1]));
}

int	export(char *input, int pid, t_term *term)
{
	char	**var;
	int		ck;
	int		plus;
	int		equal;

	ck = ck_input(input);
	if (ck)
	{
		var = export_segmentation(input);
		printf("name: |%s|  cont: |%s|\n", var[0], var[1]);
		equal = ft_strchrid(input, '=');
		plus = 0;
		if (equal != -1)
			plus = (input[equal - 1] == '+');
		if (equal != -1)
			ft_setenv(var[0], var[1], plus, term);
		else
			ft_setenv(var[0], var[1], EMPTY, term);
		free_table(var);
	}
	else
		printf("export: '%s': not a valid identifier", input);
	if (!pid)
		exit(!ck);
	return (!ck);
}

int	env(int pid, char **environ, int fd[2])
{
	int			i;

	i = 0;
	while (environ[i])
	{
		if ((ft_strccount(environ[i], '=') > 0))
		{
			ft_putstr_fd(environ[i++], fd[WRITE]);
			ft_putstr_fd("\n", fd[WRITE]);
		}
	}
	if (!pid)
		exit(0);
	return (0);
}

int	unset(char *input, int pid, char **env)
{
	if (!ft_unsetenv(input, env))
	{
		if (!pid)
			exit(0);
		return (0);
	}
	if (!pid)
		exit(1);
	return (1);
}
