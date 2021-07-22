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

char	*trans_error(char **input, char **trans, int *iter, int error)
{
	char	*new;
	char	*status;

	status = ft_itoa(error);
	new = malloc(ft_strlen(*trans) + ft_strlen(*input) + ft_strlen(status));
	ft_bzero(new, sizeof(new));
	new = ft_strjoin(*trans, status);
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
//	int		n;

	i = 0;
	while ((*input)[i] && (*input)[i] != ' ' && (*input)[i] != '\"'
		&& (*input)[i] != '$' && (*input)[i] != '\'')
		i++;
	find = ft_calloc(i + 1, 1);
	i = 0;
	while (**input && **input != ' ' && **input != '\"' && **input != '$'
		&& **input != '\'')
		find[i++] = (*(*input)++);
	*arg = ft_getenv(find, env);
	if (*arg)
		*arg = ft_strdup(ft_getenv(find, env));
	/*i = -1;
	while (env[++i])
	{
		n = 0;
		while (env[i][n] != '=')
			n++;
		if (!ft_strncmp(find, env[i], n))
			break ;
	}
	if (env[i] && !ft_strncmp(find, env[i], n))
		*arg = ft_strdup(ft_getenv(find, env));
	*/
	free(find);
}

void	ft_dollar(char **input, t_term *term, char **trans, int *iter)
{
	char	*new;
	char	*arg;

	arg = NULL;
	if (*(++(*input)) == '$')
		*trans = trans_pid(input, trans, iter);
	else if (**input == '?')
		*trans = trans_error(input, trans, iter, term->last_status);
	else if (**input != ' ' && **input != 0)
	{
		find_var(input, term->env, &arg);
		if (arg)
		{
			new = ft_strjoin(*trans, arg);
			free(*trans);
			free(arg);
			*iter = ft_strlen(new);
			*trans = new;
		}
	}
	else if ((*input)++ || 1)
		(*trans)[*iter++] = '$';
}
