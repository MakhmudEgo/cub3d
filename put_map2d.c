/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:59:17 by mizola            #+#    #+#             */
/*   Updated: 2020/08/27 20:54:15 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
    while (strt_x < end_x)
    {
        my_mlx_pixel_put(img, strt_x, strt_y, clr);
        if (strt_x == end_x - 1 && strt_y < end_y)
        {
            strt_y++;
            strt_x = x;
        }
        else
            strt_x++;
    }
}

void move_player()
{

}

void    parse_map(t_img *img)
{
    int y;
    int x;

    y = 0;
    x = 0;
	img->img = mlx_new_image(t_mlx.mlx, t_c3d.x_r, t_c3d.y_r);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->l_len, &img->endian);
    while ((t_c3d.map)[y])
    {
        while ((t_c3d.map)[y][x])
        {
            if ((t_c3d.map)[y][x] == '1')
                put_map(x, y, 0xff0000, SZ_PX, img);
            else if ((t_c3d.map)[y][x] == '0')
                put_map(x, y, 0xffffff, SZ_PX, img);
            else if ((t_c3d.map)[y][x] == '2')
                put_map(x, y, 0x0000ff, SZ_PX, img);
            else if ((t_c3d.map)[y][x] == ' ')
                put_map(x, y, 0x0, SZ_PX, img);
            else if (ft_strchr("NSEW", (t_c3d.map)[y][x]) && !t_c3d.orien)
            {
            	t_c3d.orien = (t_c3d.map)[y][x];
                img->strt_x = x * SZ_PX + (SZ_PX / 2);
				img->strt_y = y * SZ_PX + (SZ_PX / 2);;
				put_map(x, y, 0xffffff, SZ_PX, img);
			}
            else if (t_c3d.orien)
				put_map(x, y, 0xffffff, SZ_PX, img);
			x++;
        }
		x = 0;
		y++;
	}

	double bx = (int)(img->strt_x / 64) * 64 + 64;
	double by = img->strt_y + (bx - img->strt_x) * tan(t_c3d.crnr_s);
	while (bx / 64 < 29 && by / 64 < 10 && t_c3d.map[(int)(by/64)][(int)(bx/64)] != '1')
	{
		bx += 64;
		by += 64 * tan(t_c3d.crnr_s);
	}
	double lv = sqrt(pow(bx - img->strt_x, 2) + pow(by - img->strt_y, 2));
	double k = 0;
	while (k <= lv)
	{
		my_mlx_pixel_put(img, img->strt_x + k * cos(t_c3d.crnr_s), img->strt_y + k * sin(t_c3d.crnr_s), 0x0000);
		k++;

	}

	// ----------
	double bbx = (int)(img->strt_x / 64) * 64 - 1;
	double bby = img->strt_y + (img->strt_x - bbx) * tan(t_c3d.crnr_e);
	while (bbx / 64 < 29 && bby / 64 < 10 && t_c3d.map[(int)(bby/64)][(int)(bbx/64)] != '1')
	{
		bbx -= 64;
		bby -= 64 * tan(t_c3d.crnr_e);
	}
	lv = sqrt(pow(bbx - img->strt_x, 2) + pow(bby - img->strt_y, 2));
	k = 0;
	while (k <= lv)
	{
		my_mlx_pixel_put(img, img->strt_x + k * cos(t_c3d.crnr_e), img->strt_y + k * sin(t_c3d.crnr_e), 0x0000);
		k++;
	}
	// ----
	mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img->img, 0, 0);
}
