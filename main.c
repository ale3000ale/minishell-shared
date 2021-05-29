/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:45:54 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/29 15:52:30 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

/* CD use test path */

void	ft_execute_commands(int commands, char *line)
{
	line[0] = line[0];
	if (commands == MY_CLEAR)
		my_clear_screen();
	else if (commands == MY_EXIT)
		quit();
	else if (commands == MY_CD)
		change_path(line);
}

static int	find_command_support(int flag_stop, char **commands, char *line)
{
	int		index_commands;

	if (flag_stop > 0)
	{
		flag_stop = ft_parsing_hub(index_commands, line, commands);
	}
	return (flag_stop);
}

int	find_command(t_term *term)
{
	int		flag_stop;
	char	**commands;
	char	*current_path;

	commands = ft_split(COMMANDS, ',');
	flag_stop = 1;
	while (flag_stop > 0)
	{
		current_path = find_path(); // tramite la funzione getcwd trova il path della directory attuale
		graphic_hub(2, current_path); // printa le cazzate tipo l'AK 
		flag_stop = get_next_line(0, term);
		find_command_support(flag_stop, commands, term->input);
		free(term->input);
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
