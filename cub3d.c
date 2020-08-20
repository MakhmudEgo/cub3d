/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:53:39 by mizola            #+#    #+#             */
/*   Updated: 2020/08/19 19:21:20 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void		hello(int key, t_img *img)
{
//	mlx_destroy_image(t_mlx.mlx, img);
/*	img->img = mlx_new_image(t_mlx.mlx, t_cub3d.x_r, t_cub3d.y_r);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->l_len, &img->endian);*/
	if (key == 0x7e || key == 0xd)
		my_mlx_pixel_put(img, img->tmp_x, --(img->tmp_y), 0xff0000);
	if (key == 0x7d || key == 0x1)
		my_mlx_pixel_put(img, img->tmp_x, ++(img->tmp_y), 0xff0000);
	if (key == 0x7b || key == 0)
		my_mlx_pixel_put(img, --(img->tmp_x), img->tmp_y, 0xff0000);
	if (key == 0x7c || key == 0x2)
		my_mlx_pixel_put(img, ++(img->tmp_x), img->tmp_y, 0xff0000);
	printf("key == %#x\n", key);
	if (key == 0x35)
		exit(123);
	mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img->img, 0, 0);
}
//hello world

void put_map(int x, int y, int clr, int size_px, t_img *img)
{
    int end_x;
    int strt_x;
    int end_y;
    int strt_y;

    strt_y = y * size_px;
    strt_x = x * size_px;
    x = strt_x;
    end_x = strt_x + size_px;
    end_y = strt_y + size_px;
    while (strt_x <= end_x)
    {
        my_mlx_pixel_put(img, strt_x, strt_y, clr);
        if (strt_x == end_x && strt_y < end_y)
        {
            strt_y++;
            strt_x = x;
        }
        else
            strt_x++;
    }
}

void    parse_map(t_img *img)
{
    int y;
    int x;
    int size_px;

    y = 0;
    x = 0;
    size_px = 25;
    while ((t_cub3d.map)[y])
    {
        while ((t_cub3d.map)[y][x])
        {
            if ((t_cub3d.map)[y][x] == '1')
                put_map(x, y, 0xff0000, size_px, img);
            else if ((t_cub3d.map)[y][x] == '0')
                put_map(x, y, 0xffffff, size_px, img);
            else if ((t_cub3d.map)[y][x] == '2')
                put_map(x, y, 0x0000ff, size_px, img);
            else if ((t_cub3d.map)[y][x] == ' ')
                put_map(x, y, 0x0, size_px, img);
            else
			{
				put_map(x, y, 0x00ff00, size_px, img);
				img->tmp_x = x;
				img->tmp_y = y;
			}
            x++;
        }
        x = 0;
        y++;
    }
    double dd = -0.3;
    float cc = 0;
    while (dd <= 0.7)
    {
        while (1)
        {
            float xx = img->tmp_x * size_px + (size_px/2) + cc * cos(dd);
            float yy = img->tmp_y * size_px + (size_px/2) + cc * sin(dd);
            cc += 1;
            my_mlx_pixel_put(img, (int)xx, (int)yy, 0xf000f0);
//    	mlx_pixel_put(t_mlx.mlx, t_mlx.wnd, (int)yy, (int)xx, 0xff0000);
            if ((t_cub3d.map)[(int)yy/25][(int)xx/25] == '1') break;
        }
        cc = 0;
        dd += 0.01;
    }
    mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img->img, 0, 0);
}

int main(int argc, char **argv)
{
	t_img img;

	img.tmp_x = 5;
	img.tmp_y = 5;

	prs_cub3d("../cub3d.pub"); // argv[1]
	t_mlx.mlx = mlx_init();
	t_mlx.wnd = mlx_new_window(t_mlx.mlx, t_cub3d.x_r, t_cub3d.y_r, "cub3d");
	img.img = mlx_new_image(t_mlx.mlx, t_cub3d.x_r, t_cub3d.y_r);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
    parse_map(&img);
//    my_mlx_pixel_put(&img, 5, 5, 0xff0000);
//    put_map();
    mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img.img, 0, 0);
    mlx_hook(t_mlx.wnd, 2, 0L, hello, &img);
    mlx_loop(t_mlx.mlx);
}
