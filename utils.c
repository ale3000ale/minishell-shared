/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:52:41 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/15 19:00:53 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init(t_term *term, char **env)
{
	char	*level;

	level = getenv("SHLVL");
	level[0]++;
	setenv("SHLVL", level, 1);
	term->type = getenv("TERM");
	tcgetattr(0, &term->dconf);
	ft_memcpy(&term->cconf, &term->dconf, sizeof(struct termios));
	term->cconf.c_lflag &= ~(ECHO | ICANON);
	term->cursor = 0;
	term->env = env;
	open_history(term);
}

static void	intHandler(int signal)
{
	if (signal == 2)
	{
		write(1, "\n", 1);
		graphic_hub(2, find_path());
		ft_signal_manager();
	}
}

void	ft_signal_manager(void)
{
	signal(SIGINT, intHandler);
}
