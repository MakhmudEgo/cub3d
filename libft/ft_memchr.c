/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 00:06:14 by mizola            #+#    #+#             */
/*   Updated: 2020/05/03 00:35:49 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t			i;
	unsigned char	*result;

	i = 0;
	result = (unsigned char*)arr;
	while (i < n)
	{
		if (*(result + i) == (unsigned char)c)
			return (result + i);
		i++;
	}
	return (NULL);
}
