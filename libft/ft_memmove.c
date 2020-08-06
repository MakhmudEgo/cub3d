/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 19:46:55 by mizola            #+#    #+#             */
/*   Updated: 2020/05/02 23:12:21 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	if (n == 0 || source == destination)
		return (destination);
	if (destination < source)
		return (ft_memcpy(destination, source, n));
	while (n)
	{
		*((char*)destination + n - 1) = *((char*)source + n - 1);
		n--;
	}
	return (destination);
}
