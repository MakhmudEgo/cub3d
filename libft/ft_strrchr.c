/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 03:18:55 by mizola            #+#    #+#             */
/*   Updated: 2020/05/04 04:00:58 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int index;

	index = ft_strlen(s);
	while (index >= 0)
	{
		if (s[index] == (char)c)
			return ((char*)s + index);
		index--;
	}
	return (NULL);
}
