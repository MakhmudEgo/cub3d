/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:10:02 by mizola            #+#    #+#             */
/*   Updated: 2020/09/20 15:10:13 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		int_to_char(int n, unsigned char *src)
{
	src[0] = (unsigned char)(n);
	src[1] = (unsigned char)(n >> 8);
	src[2] = (unsigned char)(n >> 16);
	src[3] = (unsigned char)(n >> 24);
}

static void		bmp_hdr(t_data *data, int file_size, int fd)
{
	unsigned char bmp[54];

	ft_bzero(bmp, 54);
	bmp[0] = (unsigned char)('B');
	bmp[1] = (unsigned char)('M');
	int_to_char(file_size, bmp + 2);
	bmp[10] = (unsigned char)(54);
	bmp[14] = (unsigned char)(40);
	int_to_char(data->x_r, bmp + 18);
	int_to_char(data->y_r, bmp + 22);
	bmp[26] = (unsigned char)(1);
	bmp[28] = (unsigned char)(24);
	write(fd, bmp, 54);
}

static void		get_pxl(t_data *data, int fd)
{
	int	i;
	int	j;
	int	color;

	i = data->y_r - 1;
	while (i >= 0)
	{
		j = -1;
		while (++j < data->x_r)
		{
			color = *(int*)(data->img.addr +
			(i * data->img.l_len + j * (data->img.bpp / 8)));
			write(fd, &color, 3);
		}
		i--;
	}
}

int				screen(t_data *data)
{
	int	fd;
	int	l;

	while (data->x_r % 4 != 0)
		data->x_r--;
	l = 54 + (4 * data->y_r * data->x_r);
	if (!(fd = open("screen.bmp", O_WRONLY | O_CREAT
	| O_TRUNC | O_APPEND, 0666)))
		exit_notify("Failed screenshot\n", 2);
	bmp_hdr(data, l, fd);
	get_pxl(data, fd);
	close(fd);
	return (1);
}
