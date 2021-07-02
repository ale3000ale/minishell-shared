/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:45:54 by dlanotte          #+#    #+#             */
/*   Updated: 2021/07/02 16:07:58 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

// Generate son procecess, if they are in pipe make the pipe fd and set it
// Retrurn the pid

int	son_generation(t_clist *queque)
{
	int	pp[2];
	int	pid;

	if (get_op(queque)->pipe)
	{
		if (pipe(pp) == -1)
			exit(printf("pipe fail\n") * 0 + 1);
		get_op(queque)->fd[WRITE] = pp[WRITE];
		get_op(queque->next)->fd[READ] = pp[READ];
	}
	pid = getpid();
	if (get_op(queque)->cmd[0] && (get_op(queque)->pipe || cmd_id(get_op(queque)->cmd) == -1))
		pid = fork();
	return (pid);
}

// Execute the commands if it aren't a build-in cmd, set the correct
// in/out fd whit dup

void	ft_execute_commands(t_clist *queque, t_term *term, int pid, int red)
{
	int	commands;

	if (red == -1)
		exit(1);
	commands = cmd_id(get_op(queque)->cmd);
	if (commands == MY_CLEAR)
		term->last_status = clear_cmd(pid);
	else if (commands == MY_EXIT)
		term->last_status = quit(get_op(queque), term);
	else if (commands == MY_CD)
		term->last_status = cd(get_op(queque), pid);
	else if (commands == MY_PWD)
		term->last_status = pwd(pid, get_op(queque)->fd);
	else if (commands == MY_EXPORT)
		term->last_status = export(get_op(queque)->argv, pid, term, \
			get_op(queque)->fd);
	else if (commands == MY_UNSET)
		term->last_status = unset(get_op(queque)->argv, pid, term);
	else if (commands == MY_ENV)
		term->last_status = env(pid, term->env, get_op(queque)->fd);
	else if (commands == MY_ECHO)
		term->last_status = my_echo(get_op(queque), pid);
	else
	{
		if (get_op(queque)->fd[WRITE] > 1 )
			dup2(get_op(queque)->fd[WRITE], WRITE);
		if (get_op(queque)->fd[READ])
			dup2(get_op(queque)->fd[READ], READ);
		exec_cmd(get_op(queque), pid, term->env);
	}
}

// Maneging the cmd request, create son process and manege it

void	exec_manager(t_clist *queque, t_term *term)
{
	int		pid;
	int		red;
	char	*fd_error;

	fd_error = 0;
	red = 0;
	if (get_op(queque)->red)
		red = redirection(get_op(queque), &fd_error);
	pid = son_generation(queque);
	if (get_op(queque)->cmd[0] && ((pid && !get_op(queque)->pipe \
		&& cmd_id(get_op(queque)->cmd) > -1) || (!pid)))
		ft_execute_commands(queque, term, pid, red);
	else
	{
		waitpid(pid, &term->last_status, 0);
		if (red == -1)
		{
			term->last_status = 1;
			ft_putstr_fd("miniasciihell: ", 1);
			ft_putstr_fd(fd_error, 1);
			ft_putstr_fd(": No such file or directory\n", 1);
		}
		if (get_op(queque)->fd[WRITE] > 1)
			close(get_op(queque)->fd[WRITE]);
		if (get_op(queque)->fd[READ] > 0)
			close(get_op(queque)->fd[READ]);
	}
	term->last_status = term->last_status >> 8;
	if (term->last_status == 127)
		error404(get_op(queque)->cmd, 1, term);
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
		ft_parsing_hub(term);
	}
	free_table(commands);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_term	term;

	argc = 0;
	argv[0] = argv[0];
	init(&term, env);
	g_term = &term;
	write(1, "", 1);
	my_clear_screen();
	ft_signal_manager();
	find_command(&term);
	return (0);
}
