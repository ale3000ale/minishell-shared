/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanotte <dlanotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 17:26:02 by dlanotte          #+#    #+#             */
/*   Updated: 2021/05/20 17:31:13 by dlanotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*ps;
	unsigned char	*pd;

	if (!dst && !src)
		return (0);
	ps = (unsigned char *)src;
	pd = (unsigned char *)dst;
	i = 0;
	while (i < n)
	{
		pd[i] = ps[i];
		i++;
	}
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	if (!dst || !src)
		return (0);
	i = ft_strlen(src);
	if (dstsize <= 1)
	{
		if (dstsize)
			dst[0] = '\0';
		return (i);
	}
	if (i < dstsize - 1)
		dstsize = i + 1;
	ft_memcpy(dst, src, dstsize - 1);
	dst[dstsize - 1] = '\0';
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(dst);
	while (i + j + 1 < dstsize && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	if (i < dstsize)
	{
		dst[i + j] = '\0';
	}
	else
		i = dstsize;
	return (i + ft_strlen(src));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	dstsize;

	if (!s1 || !s2)
		return (NULL);
	dstsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = (char *)malloc(dstsize * sizeof(char));
	if (dst)
	{
		ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
		ft_strlcat(dst, s2, dstsize);
	}
	return (dst);
}
