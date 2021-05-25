/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zxcvbinz <zxcvbinz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:52:41 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/26 00:13:17 by zxcvbinz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	init(t_term *term)
{
	term->type = getenv("TERM");
	tcgetattr(0, &term->dconf);
	ft_memcpy(&term->cconf, &term->dconf, sizeof(struct termios));
	term->cconf.c_lflag &= ~(ECHO | ICANON);
	//term->cconf.c_cc[VMIN] = 1;
	//term->cconf.c_cc[VTIME] = 0;
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
