/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 05:53:54 by mizola            #+#    #+#             */
/*   Updated: 2020/05/20 04:55:22 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_equal(const char *haystack, const char *needle,
						size_t len, size_t *index)
{
	size_t index1;

	index1 = 0;
	while (haystack[*index] != '\0' && needle[index1] != '\0'
			&& *index < len)
	{
		if (haystack[*index] != needle[index1])
		{
			*index = *index - index1;
			break ;
		}
		index1 += 1;
		*index += 1;
	}
	return (index1);
}

char			*ft_strnstr(const char *haystack, const char *needle,
							size_t len)
{
	size_t index;
	size_t index1;
	size_t res;

	index = 0;
	res = ft_strlen(needle);
	if (res == 0)
		return ((char*)haystack);
	while (haystack[index] != '\0' && index < len)
	{
		index1 = is_equal(haystack, needle, len, &index);
		if (index1 == res)
			return ((char*)haystack + (index - index1));
		index++;
	}
	return (NULL);
}
