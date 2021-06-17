#include "./includes/minishell.h"

char	*trans_pid(char **input, char **trans, int *iter)
{
	char	*pid;
	char	*new;

	pid = ft_itoa(getpid());
	new = malloc(ft_strlen(*trans) + ft_strlen(*input) + ft_strlen(pid));
	ft_bzero(new, sizeof(new));
	new = ft_strjoin(*trans, pid);
	free(*trans);
	(*input)++;
	if (**input == '\"')
		(*input)++;
	*iter = ft_strlen(new);
	return (new);
}

void	find_var(char **input, char **env, char **arg)
{
	char	*find;
	int		i;

	i = 0;
	while ((*input)[i] && (*input)[i] != ' ' && (*input)[i] != '\"'
		&& (*input)[i] != '$' && (*input)[i] != '\'')
		i++;
	find = malloc(i + 1);
	i = 0;
	while (**input && **input != ' ' && **input != '\"' && **input != '$'
		&& **input != '\'')
	{
		find[i++] = **input;
		(*input)++;
	}
	find[i] = 0;
	i = -1;
	while (env[++i] && ft_strncmp(find, env[i], ft_strlen(find)))
		;
	if (env[i] && !ft_strncmp(find, env[i], ft_strlen(find)))
		*arg = ft_strdup(env[i] + ft_strlen(find) + 1);
	free(find);
}

char	*ft_dollar(char **input, char **env, char **trans, int *iter)
{
	char	*new;
	char	*arg;

	arg = 0;
	(*input)++;
	if (**input == '$')
		return (trans_pid(input, trans, iter));
	if (**input != ' ' && **input != 0)
	{
		find_var(input, env, &arg);
		if (!arg)
			return (*trans);
		new = malloc(ft_strlen(*trans) + ft_strlen(arg) + ft_strlen(*input));
		ft_bzero(new, sizeof(new));
		new = ft_strjoin(*trans, arg);
		free(*trans);
		*iter = ft_strlen(new);
		return (new);
	}
	(*trans)[*iter] = '$';
	(*iter)++;
	(*input)++;
	return (*trans);
}
