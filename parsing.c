/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:02:58 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/29 15:49:24 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	ft_check_commands(char **operations, int index, char *line)
{
	char	*op;

	op = operations[index];
	if (op == NULL)
		return (-1);
	if ((ft_strlen(line) == ft_strlen(op)) \
		&& !ft_strncmp(line, op, ft_strlen(op)))
		return (index);
	return (ft_check_commands(operations, index + 1, line));
}

void	ft_commands_hub(char **str_pars, char **commands)
{
	int	i;
	int	commands_counter;

	i = 0;
	commands_counter = 0;
	while (str_pars[i])
	{
		if (ft_check_commands(commands, 0, str_pars[i]) > -1)
			commands_counter++;
		i++;
	}
}

int	ft_parsing_hub(int index_commands, char *line, char **commands)
{
	char	**string_parsing;

	string_parsing = ft_split(line, ' ');
	index_commands = ft_check_commands(commands, 0, string_parsing[0]);
	write(1, "\n", 1);
	printf("\033[0m\033[0;37m");
	if (index_commands > -1)
		ft_commands_hub(string_parsing, commands);
	else
		error404(line);
	return (1);
}
