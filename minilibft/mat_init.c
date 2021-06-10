/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarcell <amarcell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 12:49:37 by amarcell          #+#    #+#             */
/*   Updated: 2021/06/10 16:56:57 by amarcell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	**mat_init(int dim, int h)
{
	void	**mat;

	mat = ft_calloc(1, dim * (h + 1));
	if (!mat)
		return (0);
	return (mat);
}
