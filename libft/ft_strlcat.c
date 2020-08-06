/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 03:08:59 by mizola            #+#    #+#             */
/*   Updated: 2020/05/03 23:52:11 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i_dst;
	size_t i_src;
	size_t index;
	size_t size_all;

	i_dst = ft_strlen(dst);
	i_src = ft_strlen(src);
	size_all = i_dst + i_src;
	index = 0;
	if (i_dst >= size)
		return (size + i_src);
	while (i_dst < size - 1 && src[index] != '\0')
	{
		dst[i_dst] = src[index];
		i_dst++;
		index++;
	}
	dst[i_dst] = '\0';
	return (size_all);
}
