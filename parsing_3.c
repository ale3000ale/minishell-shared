#include "includes/minishell.h"

char	*ft_dollar(char **input, char **env, char **trans, int *iter)
{
	char	*new;
	char	*find;
	char	*arg;
	int		i;

	(*input)++;
	//funzione pid
	if (**input == '$')
	{
		char *pid;
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
	//fine funzione pid
	if (**input != ' ' && **input != 0)
	{
		//funzione trova var in env
		i = 0;
		while ((*input)[i] && (*input)[i] != ' ' && (*input)[i] != '\"' && (*input)[i] != '$')
			i++;
		find = malloc(i + 1);
		i = 0;
		while (**input && **input != ' ' && **input != '\"' && **input != '$')
		{
			//printf("%c\n", **input);
			find[i++] = **input;
			(*input)++; 
		}
		find[i] = 0;
		i = 0;
		arg = 0;
		while (env[i])
		{
			if (!ft_strncmp(find, env[i], ft_strlen(find)))
			{
				arg = ft_strdup(env[i] + ft_strlen(find) + 1);
				break ;
			}
			i++;
		}
		if (!arg)
			return (*trans);
		new = malloc(ft_strlen(*trans) + ft_strlen(arg) + ft_strlen(*input));
		ft_bzero(new, sizeof(new));
		new = ft_strjoin(*trans, arg);
		free(*trans);
		if (**input == '\"')
			(*input)++;
		*iter = ft_strlen(new);
		return (new);
	}
	(*trans)[*iter] = '$';
	(*iter)++;
	(*input)++;
	return (*trans);
}

char *ft_translate(char *input, char **env)
{
	char	*trans;
	int		iter;	

//traduci tutta la linea caratter per carattere, se trovi apice copia tutto quello che è dentro apice, se virgolette
//stessa cosa di apice ma traduci dollaro, se dollaro traduci, sennò copia.
	iter = 0;
	trans = malloc(ft_strlen(input));
	ft_bzero(trans, ft_strlen(input));
	while (*input)
	{
		if (*input == ' ')
		{
			trans[iter++] = *input;
			while (*input && *input == ' ')
				input++;
		}
		if (*input == '\\')
		{
			input++;
			trans[iter++] = *input;
			input++;
		}
		else if (*input == '\'')
		{
			input++;
			while (*input && *input != '\'')
			{
				trans[iter++] = *input;
				input++;
			}
			input++;
		}
		else if (*input == '\"')
		{
			input++;
			while (*input && *input != '\"')
			{
				if (*input == '$')
					trans = ft_dollar(&input, env, &trans, &iter);
				else
				{
					trans[iter++] = *input;
					input++;
				}
			}
		}
		else if (*input == '$')
			trans = ft_dollar(&input, env, &trans, &iter);
		else if (*input)
		{
			trans[iter++] = *input;
			input++;
		}
		//printf("loop=%s\n", trans);
	}
	trans[iter] = 0;
	return (trans);
}