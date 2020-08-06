/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 20:45:25 by mizola            #+#    #+#             */
/*   Updated: 2020/05/14 20:17:04 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	char_set(const char *set, char c)
{
	unsigned int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		start;
	int		finish;

	i = 0;
	start = 0;
	if (!s1 || !set)
		return (NULL);
	finish = ft_strlen(s1) - 1;
	while (s1[start] != '\0' && (s1[start] && char_set(set, s1[start])))
		start++;
	if (s1[start] == '\0')
		return ((!(str = ft_calloc(1, 1)) ? NULL : str));
	while (finish >= 0 && (s1[finish] && char_set(set, s1[finish])))
		finish--;
	str = malloc(sizeof(char) * (finish - start + 2));
	if (str == NULL)
		return (NULL);
	while (start <= finish)
		str[i++] = s1[start++];
	str[i] = '\0';
	return (str);
}
