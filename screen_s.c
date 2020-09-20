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

static	void	int_to_char(int n, unsigned char *src)
{
	src[0] = (unsigned char)(n);
	src[1] = (unsigned char)(n >> 8);
	src[2] = (unsigned char)(n >> 16);
	src[3] = (unsigned char)(n >> 24);
}

static	void	pixels(t_data *data, int fd)
{
	int		i;
	int		j;
	int		color;

	i = data->y_r - 1;
	while (0 <= i)
	{
		j = 0;
		while (j < data->x_r)
		{
			color = *(int*)(data->img.addr + (i * data->img.l_len + j * (data->img.bpp / 8)));
			write(fd, &color, 3);
			j++;
		}
		i--;
	}
}

static	void	header_bmp(t_data *data, int fd, int filesize)
{
	unsigned	char	arr[54];
	int					count;

	count = 0;
	while (count < 54)
		arr[count++] = 0;
	arr[0] = 'B';
	arr[1] = 'M';
	int_to_char(filesize, &arr[2]);
	arr[10] = (unsigned char)(54);
	arr[14] = (unsigned char)(40);
	int_to_char(data->x_r, &arr[18]);
	int_to_char(data->y_r, &arr[22]);
	arr[26] = (unsigned char)(1);
	arr[28] = (unsigned char)(24);
	write(fd, arr, 54);
}

int				save_screen(t_data *data)
{
	int		fd;
	int		filesize;

	filesize = ((data->x_r * data->y_r) * 4) + 54;
	if (((fd = open("screen.bmp", O_WRONLY | O_CREAT
				| O_TRUNC | O_APPEND, 0666))) < 0)
		return (0);
	header_bmp(data, fd, filesize);
	pixels(data, fd);
	close(fd);
	return (1);
}