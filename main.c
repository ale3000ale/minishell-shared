/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:45:54 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/04 16:29:17 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_execute_commands(int commands, char *line, t_term *term, int pipe)
{
	int	pid;

	pid = getpid();
	if (pipe)
		pid = fork();
	if (!pipe || pid)  // if pid == 0 is the child
	{
		if (commands == MY_CLEAR)
			term->last_status = clear_cmd(pid);
		else if (commands == MY_EXIT)
			quit(line);
		else if (commands == MY_CD)
			term->last_status = cd(line, pid);
		else if (commands == MY_PWD)
			term->last_status = pwd(pid);
		else if (commands == MY_EXPORT)
			term->last_status = export(line, pid);
		else if (commands == MY_UNSET)
			term->last_status = unset(line, pid);
		else if (commands == MY_ENV)
			term->last_status = env(pid);
	}
	else
	{
		wait(&term->last_status);
		term->last_status = term->last_status >> 8;
	}
}

static int	find_command_support(int flag_stop, char **commands, \
								char *line, t_term *term)
{
	if (flag_stop > 0)
		flag_stop = ft_parsing_hub(line, commands, term);
	return (flag_stop);
}

// tramite la funzione getcwd trova il path della directory attuale
// printa le cazzate tipo l'AK 

int	find_command(t_term *term)
{
	int		flag_stop;
	char	**commands;
	char	*current_path;

	commands = ft_split(COMMANDS, ',');
	flag_stop = 1;
	while (flag_stop > 0)
	{
		current_path = find_path();
		graphic_hub(2, current_path);
		flag_stop = get_next_line(0, term);
		find_command_support(flag_stop, commands, term->input, term);
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
