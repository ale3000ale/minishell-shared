/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_join_row.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:34:32 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/10 16:40:19 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	**mat_join_row(void **mat, void *row)
{
	int		i;
	void	**new;
	int		dim;

	i = 0;
	dim = mat_row(mat) + 1;
	new = mat_init(sizeof(void *), dim);
	if (!new)
		return (0);
	while (i < dim - 1)
	{
		new[i] = (mat)[i];
		i++;
	}
	free(mat);
	new[i] = row;
	return (new);
}
