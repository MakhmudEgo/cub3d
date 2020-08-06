/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 18:28:27 by mizola            #+#    #+#             */
/*   Updated: 2020/08/06 16:42:38 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen_gnl(const char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*str;
	int		i;

	i = ft_strlen_gnl(s1) + 1;
	str = (char*)malloc(sizeof(*str) * i);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	while (i < len && s[start] != '\0')
	{
		str[i] = s[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_gnl(char *s1, char const *s2)
{
	char			*str;
	unsigned int	len;
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = 0;
	len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1;
	str = (char*)malloc(len);
	if (str == NULL)
		return (NULL);
	while (s1 && s1[n] != '\0')
		str[i++] = s1[n++];
	n = 0;
	while (s2[n] != '\0')
		str[i++] = s2[n++];
	str[i] = '\0';
	free(s1);
	return (str);
}
