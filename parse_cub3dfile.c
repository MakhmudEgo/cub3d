/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub3dfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:30:40 by mizola            #+#    #+#             */
/*   Updated: 2020/08/06 17:34:21 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void t_cub3d_init()
{
	t_cub3d.map = 0x0;
	t_cub3d.x_r = 0x0;
	t_cub3d.y_r = 0x0;
	t_cub3d.no_t = 0x0;
	t_cub3d.so_t = 0x0;
	t_cub3d.we_t = 0x0;
	t_cub3d.ea_t = 0x0;
	t_cub3d.sp_t = 0x0;
	t_cub3d.st_t = 0x0;
	t_cub3d.ft_t = 0x0;
	t_cub3d.f_t = 0x0;
	t_cub3d.c_t = 0x0;
}

void prs_cub3d_ass(char *s)
{
	if (*s == 'R')
	{
		s++;
		t_cub3d.x_r = ft_atoi(s);
		s++;
		while (*s && *s != ' ' && *s != '\0')
			s++;
		t_cub3d.y_r = ft_atoi(s);
	}
	else if (*s == 'N' && *(s + 1) == 'O')
		t_cub3d.no_t = ft_strdup(s + 3);
	else if (*s == 'S' && *(s + 1) == 'O')
		t_cub3d.so_t = ft_strdup(s + 3);
	else if (*s == 'W' && *(s + 1) == 'E')
		t_cub3d.we_t = ft_strdup(s + 3);
	else if (*s == 'E' && *(s + 1) == 'A')
		t_cub3d.ea_t = ft_strdup(s + 3);
	else if (*s == 'S' && *(s + 1) != 'O')
		t_cub3d.sp_t = ft_strdup(s + 3);
	else if (*s == 'S' && *(s + 1) == 'T')
		t_cub3d.st_t = ft_strdup(s + 3);
	else if (*s == 'F' && *(s + 1) == 'T')
		t_cub3d.ft_t = ft_strdup(s + 3);
}

void prs_cub3d(char *argv)
{
	char *line;
	int fd;
	int i;

	i = 1;
	t_cub3d_init();
	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		prs_cub3d_ass(line);
		free(line);
		i++;
	}
	printf("%d\n", i);
}