/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zxcvbinz <zxcvbinz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:45:54 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/26 00:12:28 by zxcvbinz         ###   ########.fr       */
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
	if (commands == MY_CLEAR)
		my_clear_screen();
	else if (commands == MY_EXIT)
		quit();
	else if (commands == MY_CD)
		change_path(getenv("USER"));
}

static int	find_command_support(int flag_stop, char **commands, char *line)
{
	int		index_commands;

	if (flag_stop > 0)
	{
		index_commands = ft_check_commands(commands, 0, line);
		write(1, "\n", 1);
		if (index_commands > -1)
			ft_execute_commands(index_commands, line);
		else
			error404(line);
	}
	return (flag_stop);
}

int	find_command(t_term *term)
{
	int		flag_stop;
	char	*line;
	char	**commands;
	char	*current_path;

	commands = ft_split(COMMANDS, ',');
	flag_stop = 1;
	while (flag_stop > 0)
	{
		current_path = find_path();
		graphic_hub(2, current_path);
		flag_stop = get_next_line(0, &line, term);
		find_command_support(flag_stop, commands, line);
		free(line);
	}
	free_table(commands);
	return (1);
}

int	main(void)
{
	t_term	term;

	init(&term);
	fflush(stdout);
	my_clear_screen();
	ft_signal_manager();
	find_command(&term);
	return (0);
}
