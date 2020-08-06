/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 20:48:39 by mizola            #+#    #+#             */
/*   Updated: 2020/05/02 22:46:50 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	size_t i;

	i = 0;
	if (n == 0 || destination == source)
		return (destination);
	while (i < n)
	{
		*((char*)destination + i) = *((char*)source + i);
		i++;
	}
	return (destination);
}
