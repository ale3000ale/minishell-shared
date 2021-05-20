/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:45:54 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/20 19:15:09 by dlanotte         ###   ########.fr       */
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

static void	ft_execute_commands(int commands)
{
	if (commands == 0)
		clear_screen();
	else if (commands == 3)
		exit(0);
}

int	find_command(void)
{
	int		flag_stop;
	char	**line;
	char	**commands;
	int		index_commands;

	commands = ft_split("clear,env,echo,exit", ',');
	line = malloc(sizeof(char *));
	flag_stop = 1;
	while (flag_stop > 0)
	{
		graphic_hub(2, "~/demo_path/Desktop");
		flag_stop = get_next_line(0, line);
		if (flag_stop > 0)
		{
			index_commands = ft_check_commands(commands, 0, *line);
			if (index_commands > -1)
				ft_execute_commands(index_commands);
		}
		free(*line);
	}
	free_table(commands);
	free(line);
	return (1);
}

int	main(void)
{
	clear_screen();
	graphic_hub(1, "");
	clear_screen();
	ft_signal_manager();
	find_command();
	return (0);
}
