/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 15:45:54 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/20 17:39:04 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static int	find_command(void)
{
	int		flag_stop;
	char	**line;

	line = malloc(sizeof(char *));
	flag_stop = 1;
	while (flag_stop > 0)
	{
		graphic_hub(2, "~/demo_path/Desktop");
		flag_stop = get_next_line(0, line);
		if (flag_stop > 0)
		{
			printf("%s\n", *line);
		}
		free(*line);
	}
	free(line);
	return (1);
}

int	main(void)
{
	printf("\e[1;1H\e[2J");
	find_command();
	return (0);
}
