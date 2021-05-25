/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zxcvbinz <zxcvbinz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:18:50 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/26 00:12:07 by zxcvbinz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_idle(char *path)
{
	printf("\033[0;37m┏━━━[\033[0;36m%s\033[0;37m]━━━━━━━ \
hello. \033[0;35m%s\033[0;37m\n", path, getenv("USER"));
	write(1, "\033[0;37m┗━━━ \033[0;31m\033[31m︻\033[0m\033[32m┳\033[0m\033[33m\
デ\033[0m\033[34m═\033[0m\033[35m—\033[0m\033[0;37m $> ", \
	ft_strlen("\033[0;37m┗━━━ \033[0;31m\033[31m︻\033[0m\033[32m┳\033[0m\033[33m\
デ\033[0m\033[34m═\033[0m\033[35m—\033[0m\033[0;37m $> "));
	write(1, TEXT_COLOR, ft_strlen(TEXT_COLOR));
}

int	graphic_hub(int select, char *path)
{
	if (select == 2)
		print_idle(path);
	return (1);
}
