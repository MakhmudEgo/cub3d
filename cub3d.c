/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:53:39 by mizola            #+#    #+#             */
/*   Updated: 2020/08/23 13:26:17 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

void		start(int key, t_img *img)
{
/*
 * img->img = mlx_new_image(t_mlx.mlx, t_c3d.x_r, t_c3d.y_r);
 * img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->l_len, &img->endian);
 */
	if (UP)
	{

	}
//		my_mlx_pixel_put(img, img->strt_x, --(img->strt_y), 0xff0000);
	if (DOWN)
	{

	}
//		my_mlx_pixel_put(img, img->strt_x, ++(img->strt_y), 0xff0000);
	if (LEFT)
	{
		t_c3d.crnr -= 0.2;
		t_c3d.crnr_s = t_c3d.crnr - 0.52;
		t_c3d.crnr_e = t_c3d.crnr + 0.52;
		parse_map(img);
	}
//		my_mlx_pixel_put(img, --(img->strt_x), img->strt_y, 0xff0000);
	if (RIGHT)
	{
		t_c3d.crnr += 0.2;
		t_c3d.crnr_s = t_c3d.crnr - 0.52;
		t_c3d.crnr_e = t_c3d.crnr + 0.52;
		parse_map(img);
	}
//		my_mlx_pixel_put(img, ++(img->strt_x), img->strt_y, 0xff0000);
	printf("key == %#x\n", key);
	if (key == 0x35)
		exit(123);
	mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img->img, 0, 0);
}

int main(int argc, char **argv)
{
	t_img img;

	img.strt_x = 5;
	img.strt_y = 5;
	(argc != 2) ? exit(45) : printf("фисё окк\n");
	prs_cub3d(argv[1]);
	t_mlx.mlx = mlx_init();
	t_mlx.wnd = mlx_new_window(t_mlx.mlx, t_c3d.x_r, t_c3d.y_r, "cub3d");
	img.img = mlx_new_image(t_mlx.mlx, t_c3d.x_r, t_c3d.y_r);
    img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
    parse_map(&img);
    mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img.img, 0, 0);
    mlx_hook(t_mlx.wnd, 2, 0L, start, &img);
    mlx_loop(t_mlx.mlx);
	return (0);
}
