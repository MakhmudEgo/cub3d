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
	while (t_c3d.crnr_s <= t_c3d.crnr_e)
	{
		int x = (int)(t_c3d.plyr_x / SZ_PX);
		int y = (int)(t_c3d.plyr_y / SZ_PX);
		printf("До:X:%d-Y%d\n", x,y);
		while (GAME)
		{
			t_c3d.plyr_x = img->strt_x + t_c3d.cf_rcs * cos(t_c3d.crnr_s);
			t_c3d.plyr_y = img->strt_y + t_c3d.cf_rcs * sin(t_c3d.crnr_s);
			t_c3d.cf_rcs += 0.5;
			x = (int)(t_c3d.plyr_x / SZ_PX);
			y = (int)(t_c3d.plyr_y / SZ_PX);
			if (!ft_strchr("02NSWE", t_c3d.map[y][x])
//			|| t_c3d.map[(int)(floor((t_c3d.plyr_y + 2) / SZ_PX))][(int)(floor((t_c3d.plyr_x + 2) / SZ_PX))] == '1'
//			&& t_c3d.map[(int)(floor((t_c3d.plyr_y - 2) / SZ_PX))][(int)(floor((t_c3d.plyr_x - 2) / SZ_PX))] == '1'
			) {
				break;
			}
//			printf("X:%d-Y%d\n", x,y);
			my_mlx_pixel_put(img, t_c3d.plyr_x, t_c3d.plyr_y, 0xf000f0);
		}
		printf("После:X:%d-Y%d\n", x,y);
		t_c3d.cf_rcs = 0;
		t_c3d.crnr_s += 0.01;
	}
	mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img->img, 0, 0);
}
