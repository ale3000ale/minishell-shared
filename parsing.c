/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:02:58 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/04 16:14:50 by amarcell         ###   ########.fr       */
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

void	ft_commands_hub(char **str_pars, char **commands, t_term *term)
{
	int	i;
	int	commands_counter;
	int	command;

	i = 0;
	commands_counter = 0;
	while (str_pars[i])
	{
		command = ft_check_commands(commands, 0, str_pars[i]);
		if (command > -1)
		{
			if (str_pars[1])
				ft_execute_commands(command, str_pars[1], term, 0);
			else
				ft_execute_commands(command, "", term, 0);
		}
		if (ft_check_commands(commands, 0, str_pars[i]) > -1)
			commands_counter++;
		i++;
	}
}

int	ft_parsing_hub(char *line, char **commands, t_term *term)
{
	char	**string_parsing;

	string_parsing = ft_split(line, ' ');
	write(1, "\n", 1);
	printf("\033[0m\033[0;37m");
	if (ft_check_commands(commands, 0, string_parsing[0]) > -1)
		ft_commands_hub(string_parsing, commands, term);
	else
		error404(line, 1);
	return (1);
}
