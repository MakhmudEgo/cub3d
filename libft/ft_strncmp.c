/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 07:27:35 by mizola            #+#    #+#             */
/*   Updated: 2020/05/04 08:11:15 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t index;

	index = 0;
	if (n == 0)
		return (0);
	while (str1[index] != '\0' && index < n - 1)
	{
		if (str1[index] != str2[index])
			return ((unsigned char)str1[index] - (unsigned char)str2[index]);
		index++;
	}
	return ((unsigned char)str1[index] - (unsigned char)str2[index]);
}
