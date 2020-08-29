/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 20:38:08 by mizola            #+#    #+#             */
/*   Updated: 2020/08/29 21:55:42 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	one_line(char **line, char **rmns, int i)
{
	*line = ft_substr_gnl(*rmns, 0, i + 1);
	if (*rmns)
		free(*rmns);
	*rmns = 0x0;
	return (!(*line) ? -1 : 0);
}

static int	line_break(char **rmns, char **line, int i)
{
	char *tmp;

	*line = ft_substr_gnl(*rmns, 0, i);
	tmp = ft_strdup_gnl(*rmns + i + 1);
	free(*rmns);
	*rmns = tmp;
	if (!(*line) || !tmp)
	{
		if (tmp)
			free(tmp);
		return (-1);
	}
	return (1);
}

static int	if_zero(char **rmns, char **line)
{
	char	*tmp;
	char	*rmnsptr;
	int		i;

	i = 0;
	rmnsptr = *rmns;
	while (rmnsptr && rmnsptr[i] != '\0')
	{
		if (rmnsptr[i] == '\n')
		{
			*line = ft_substr_gnl(*rmns, 0, i);
			tmp = ft_substr_gnl(rmnsptr, i + 1, ft_strlen_gnl(rmnsptr) - i + 1);
			free(*rmns);
			*rmns = tmp;
			return (!(*line) || !tmp ? -1 : 1);
		}
		i++;
	}
	if (rmnsptr && rmnsptr[i] == '\0')
		return (one_line(line, rmns, i));
	return (!(*line = ft_strdup_gnl("")) ? -1 : 0);
}

static int	gnl_ass(int fd, char **line, char **rmns)
{
	char		strread[BUFFER_SIZE + 1];
	int			i;
	int			n;
	char		*rmnsptr;

	i = 0;
	while ((n = read(fd, strread, BUFFER_SIZE)) > 0)
	{
		strread[n] = '\0';
		rmnsptr = ft_strdup_gnl(rmns[fd]);
		if (rmns[fd])
			free(rmns[fd]);
		if (!rmnsptr || !(rmns[fd] = ft_strjoin_gnl(rmnsptr, strread)))
			return (-1);
		while (rmns[fd][i] != '\0')
		{
			if (rmns[fd][i] == '\n')
				return (line_break(&rmns[fd], line, i));
			i++;
		}
	}
	if ((rmns[fd] && rmns[fd][i] == '\0'))
		return (one_line(line, &rmns[fd], i));
	return (n == 0 ? if_zero(&rmns[fd], line) : -1);
}

int			get_next_line(int fd, char **line)
{
	static char *rmns[256];

	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	return (gnl_ass(fd, line, rmns));
}
