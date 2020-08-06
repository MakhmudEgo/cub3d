/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 02:46:32 by mizola            #+#    #+#             */
/*   Updated: 2020/05/02 05:47:20 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	unsigned int i;

	i = 0;
	while (i < n)
	{
		*((char*)destination + i) = *((char*)source + i);
		if (*((char*)destination + i) == (char)c)
			return (destination + i + 1);
		i++;
	}
	return (NULL);
}
