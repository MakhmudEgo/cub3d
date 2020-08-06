/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 17:28:02 by mizola            #+#    #+#             */
/*   Updated: 2020/05/14 20:16:52 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;
	unsigned int	len;
	unsigned int	i;
	unsigned int	n;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	i = 0;
	n = 0;
	str = (char*)malloc(len);
	if (str == NULL)
		return (NULL);
	while (s1[n] != '\0')
		str[i++] = s1[n++];
	n = 0;
	while (s2[n] != '\0')
		str[i++] = s2[n++];
	str[i] = '\0';
	return (str);
}
