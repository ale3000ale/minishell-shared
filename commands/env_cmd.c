/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexmarcelli <alexmarcelli@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:49:54 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/23 11:42:15 by alexmarcell      ###   ########.fr       */
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

static int	export_view(int pid, char **environ, int fd[2])
{
	int		i;
	char	**spl;
	char	**tmp;

	tmp = mat_dup(environ);
	ft_sort_matrix(tmp, mat_row((void **)tmp));
	i = 0;
	while (tmp[i])
	{
		ft_putstr_fd("declare -x ", fd[WRITE]);
		if (ft_strchrid(tmp[i], '=') != -1)
		{
			spl = ft_strcut(tmp[i], ft_strchrid(tmp[i], '=') + 1);
			ft_putstr_fd(spl[0], fd[WRITE]);
			ft_putstr_fd("\"", fd[WRITE]);
			ft_putstr_fd(spl[1], fd[WRITE]);
			ft_putstr_fd("\"", fd[WRITE]);
			free_table(spl);
		}
		else
			ft_putstr_fd(tmp[i], fd[WRITE]);
		ft_putstr_fd("\n", fd[WRITE]);
		i++;
	}
	free_table(tmp);
	if (!pid)
		exit(0);
	return (0);
}

int	export(char *input, int pid, t_term *term, int *fd)
{
	char	**var;
	int		ck;
	int		equal;

	input = ft_translate(input, term);
	ck = ck_input(input);
	printf("|%s|\n", input);
	if (!input[0])
		ck = export_view(pid, term->env, fd);
	else if (ck)
	{
		var = export_segmentation(input);
		printf("name: |%s|  cont: |%s|\n", var[0], var[1]);
		equal = ft_strchrid(input, '=');
		if (equal == -1)
			ft_setenv(var[0], var[1], EMPTY, term);
		else if (input[equal - 1] == '+')
			ft_setenv(var[0], var[1], JOIN, term);
		else
			ft_setenv(var[0], var[1], OVERWRITE, term);
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
	int	i;

	i = 0;
	while (environ[i])
	{
		if ((ft_strccount(environ[i], '=') > 0))
		{
			ft_putstr_fd(environ[i], fd[WRITE]);
			ft_putstr_fd("\n", fd[WRITE]);
		}
		i++;
	}
	if (!pid)
		exit(0);
	return (0);
}

int	unset(char *input, int pid, t_term *term)
{
	input = ft_translate(input, term);
	if (!ft_unsetenv(input, term->env))
	{
		if (!pid)
			exit(0);
		return (0);
	}
	if (!pid)
		exit(1);
	return (1);
}
