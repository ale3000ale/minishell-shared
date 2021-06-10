/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 15:02:58 by dlanotte          #+#    #+#             */
/*   Updated: 2021/06/09 18:48:29 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	ft_parsing_hub(char *line, char **commands, t_term *term)
{
	char	**string_parsing;

	commands[0] = commands[0];
	string_parsing = ft_split(line, ' ');
	write(1, "\n", 1);
	printf("\033[0m\033[0;37m");
	ft_execute_commands(string_parsing[0], &line[ft_strlen(string_parsing[0])], \
		term, 0);
	free_table(string_parsing);
	return (1);
}
