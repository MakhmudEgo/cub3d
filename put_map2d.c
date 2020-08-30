/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:59:17 by mizola            #+#    #+#             */
/*   Updated: 2020/08/23 12:57:21 by mizola           ###   ########.fr       */
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

void draw_t(t_img *img, double lv, int x)
{
//	lv *= cos(t_c3d.crnr - t_c3d.crnr_s);
	int start = t_c3d.y_r / 2 - (t_c3d.y_r / lv * SZ_PX) / 2;
	int end = t_c3d.y_r / 2 + (t_c3d.y_r / lv * SZ_PX) / 2;
	if (start < 0)
		start = 0;
	while (start < end && start < t_c3d.y_r)
	{
		my_mlx_pixel_put(img, x, start++, 0x00ff00);
	}
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
				img->strt_y = y * SZ_PX + (SZ_PX / 2);
				put_map(x, y, 0xffffff, SZ_PX, img);
			}
            else if (t_c3d.orien)
				put_map(x, y, 0xffffff, SZ_PX, img);
			x++;
        }
		x = 0;
		y++;
	}
	int xx = 0;
    double step = (M_PI/3)/t_c3d.x_r;
	while (t_c3d.crnr_s < t_c3d.crnr_e)
	{
		while (GAME)
		{
			t_c3d.plyr_x = img->strt_x + t_c3d.cf_rcs * cos(t_c3d.crnr_s);
			t_c3d.plyr_y = img->strt_y + t_c3d.cf_rcs * sin(t_c3d.crnr_s);
			t_c3d.cf_rcs += 1;
			my_mlx_pixel_put(img, t_c3d.plyr_x, t_c3d.plyr_y, 0xf000f0);
			if (t_c3d.map[(int)(t_c3d.plyr_y / SZ_PX)][(int)(t_c3d.plyr_x / SZ_PX)] == '1'
			||
			t_c3d.map[(int)((t_c3d.plyr_y - 1) / SZ_PX)][(int)((t_c3d.plyr_x + 1)/ SZ_PX)] == '1'
			&& t_c3d.map[(int)((t_c3d.plyr_y + 1) / SZ_PX)][(int)((t_c3d.plyr_x - 1)/ SZ_PX)] == '1'
			||
			t_c3d.map[(int)((t_c3d.plyr_y - 1) / SZ_PX)][(int)((t_c3d.plyr_x - 1)/ SZ_PX)] == '1'
			&& t_c3d.map[(int)((t_c3d.plyr_y + 1) / SZ_PX)][(int)((t_c3d.plyr_x + 1)/ SZ_PX)] == '1'
			)
				break;
		}
		double lv = sqrt(pow(t_c3d.plyr_x - img->strt_x, 2) + pow(t_c3d.plyr_y - img->strt_y, 2));
		draw_t(img, lv, xx++);
		t_c3d.cf_rcs = 0;
		t_c3d.crnr_s += step;
	}
	printf("dd%d\n", xx);
	mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img->img, 0, 0);
}
