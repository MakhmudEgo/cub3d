/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:53:39 by mizola            #+#    #+#             */
/*   Updated: 2020/08/09 18:28:01 by mizola           ###   ########.fr       */
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
	img->img = mlx_new_image(t_mlx.mlx, t_cub3d.x_r, t_cub3d.y_r);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->l_len, &img->endian);
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
    my_mlx_pixel_put(&img, 5, 5, 0xff0000);
    mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img.img, 0, 0);
    mlx_hook(t_mlx.wnd, 2, 0L, hello, &img);
    mlx_loop(t_mlx.mlx);

//    while (GAME)
//	{
//
//		break;
//	}
}
