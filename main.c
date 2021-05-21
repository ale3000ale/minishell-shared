/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zxcvbinz <zxcvbinz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:45:54 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/21 23:19:26 by zxcvbinz         ###   ########.fr       */
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

/* CD use test path */

static void	ft_execute_commands(int commands, char *line)
{
	line[0] = line[0];
	if (commands == CLEAR)
		clear_screen();
	else if (commands == EXIT)
		quit();
	else if (commands == CD)
		change_path("..");
}

int	find_command(void)
{
	int		flag_stop;
	char	**line;
	char	**commands;
	int		index_commands;
	char	*current_path;

	commands = ft_split(COMMANDS, ',');
	line = malloc(sizeof(char *));
	flag_stop = 1;
	while (flag_stop > 0)
	{
		current_path = find_path();
		graphic_hub(2, current_path);
		flag_stop = get_next_line(0, line);
		if (flag_stop > 0)
		{
			index_commands = ft_check_commands(commands, 0, *line);
			if (index_commands > -1)
				ft_execute_commands(index_commands, *line);
			else
				error404(*line);
		}
		free(*line);
	}
	free_table(commands);
	free(line);
	return (1);
}

int	main(void)
{
	fflush(stdout);
	clear_screen();
	graphic_hub(1, "");
	clear_screen();
	ft_signal_manager();
	find_command();
	return (0);
}
