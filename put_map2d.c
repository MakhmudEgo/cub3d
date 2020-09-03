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

int		get_xpm_color(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	return (*(unsigned int*)dst);
}

void draw_t(t_img *img, double lv, int x)
{
	lv *= cos(t_c3d.crnr - t_c3d.crnr_s);
	int start = t_c3d.y_r / 2 - (t_c3d.y_r / lv * SZ_PX) / 2;
	int end = t_c3d.y_r / 2 + (t_c3d.y_r / lv * SZ_PX) / 2;
	double cff_ea = (double)t_txtr.txtr_ea.h_xpm / (end - start);
	double cff_we = (double)t_txtr.txtr_we.h_xpm / (end - start);
	double cff_so = (double)t_txtr.txtr_we.h_xpm / (end - start);
	double cff_no = (double)t_txtr.txtr_we.h_xpm / (end - start);
	int tmp = start;
	while (start < end && start < t_c3d.y_r)//
	{
		if (start >= 0)
		{
			if (t_c3d.map[(int)(t_c3d.plyr_y) / SZ_PX][(int)(t_c3d.plyr_x - 0.25 * cos(t_c3d.crnr_s)) / SZ_PX] == '1')
			{
				if (t_c3d.map[(int)(t_c3d.plyr_y + 32) / SZ_PX][(int)(t_c3d.plyr_x) / SZ_PX] == '1')
					my_mlx_pixel_put(img, x, start, get_xpm_color(&t_txtr.txtr_ea, (int)t_c3d.plyr_x % t_txtr.txtr_ea.w_xpm, (int)((start - tmp) * cff_ea)));
				else
					my_mlx_pixel_put(img, x, start, get_xpm_color(&t_txtr.txtr_so, (int)t_c3d.plyr_x % t_txtr.txtr_so.w_xpm, (int)((start - tmp) * cff_so)));
			}
			else
			{
				if (t_c3d.map[(int)(t_c3d.plyr_y) / SZ_PX][(int)(t_c3d.plyr_x + 32) / SZ_PX] == '1')
					my_mlx_pixel_put(img, x, start, get_xpm_color(&t_txtr.txtr_we, (int)t_c3d.plyr_y % t_txtr.txtr_we.h_xpm, (int)((start - tmp) * cff_we)));
				else
					my_mlx_pixel_put(img, x, start, get_xpm_color(&t_txtr.txtr_no, (int)t_c3d.plyr_y % t_txtr.txtr_no.h_xpm, (int)((start - tmp) * cff_no)));
			}
		}
		start++;
	}
}
//--------------------------------------sprite----------------------------
void draw_sprite(t_img *img)
{
	// абсолютное направление от игрока до спрайта (в радианах)
	double sprite_dir = atan2(t_cr_sprt.y - img->strt_y, t_cr_sprt.x - img->strt_x);
	// удаление лишних оборотов
	while (sprite_dir - t_c3d.crnr >  M_PI) sprite_dir -= 2*M_PI;
	while (sprite_dir - t_c3d.crnr < -M_PI) sprite_dir += 2*M_PI;

	// расстояние от игрока до спрайта
	double sprite_dist = sqrt(pow(img->strt_x - t_cr_sprt.x, 2) + pow(img->strt_y - t_cr_sprt.y, 2));
	size_t sprite_screen_size = t_c3d.y_r / (int)sprite_dist;
	// не забывайте, что 3D вид занимает только половину кадрового буфера,
	// таким образом, fb.w/2 для ширины экрана
	int h_offset = (sprite_dir - t_c3d.crnr)*(t_c3d.x_r/2)/(M_PI / 3) + (t_c3d.x_r/2)/2 - sprite_screen_size/2;
	int v_offset = t_c3d.y_r/2 - sprite_screen_size/2;

	for (size_t i=0; i<sprite_screen_size; i++) {
		if (h_offset+(i)<0 || h_offset+i>=t_c3d.x_r/2) continue;
		for (size_t j=0; j<sprite_screen_size; j++) {
			if (v_offset+(j)<0 || v_offset+j>=t_c3d.y_r) continue;
			my_mlx_pixel_put(img, h_offset+i, v_offset+j, 0x0);
		}
	}
}
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT
 //////// for KANAT


//--------------------------------------sprite----------------------------

void    parse_map(t_img *img)
{
    int y;
    int x;

    y = 0;
    x = 0;
	img->img = mlx_new_image(t_mlx.mlx, t_c3d.x_r, t_c3d.y_r);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->l_len, &img->endian);
	while (y < t_c3d.y_r / 2)
	{
		my_mlx_pixel_put(img, x, y, 0xffd1d8);
		if (x == t_c3d.x_r && y < t_c3d.y_r - 1)
		{
			x = 0;
			y++;
		}
		x++;
	}
	x = 0;
	while (y < t_c3d.y_r)
	{
		my_mlx_pixel_put(img, x, y, 0x75c1ff);
		if (x == t_c3d.x_r && y < t_c3d.y_r)
		{
			x = 0;
			y++;
		}
		x++;
	}
	x = 0;
	y = 0;
    while ((t_c3d.map)[y])
    {
        while ((t_c3d.map)[y][x])
        {
            if (ft_strchr("NSEW", (t_c3d.map)[y][x]) && !t_c3d.orien)
            {
            	t_c3d.orien = (t_c3d.map)[y][x];
                img->strt_x = x * SZ_PX + (SZ_PX / 2);
				img->strt_y = y * SZ_PX + (SZ_PX / 2);
			}
			x++;
        }
		x = 0;
		y++;
	}
	int xx = 0;
    double step = 0;
	while (step < M_PI / 3)
	{
		while (GAME)
		{
			t_c3d.plyr_x = img->strt_x + t_c3d.cf_rcs * cos(t_c3d.crnr_s);
			t_c3d.plyr_y = img->strt_y + t_c3d.cf_rcs * sin(t_c3d.crnr_s);
			t_c3d.cf_rcs += 0.25;
			my_mlx_pixel_put(img, t_c3d.plyr_x/8, t_c3d.plyr_y/8, 0xffff66);
			if (t_c3d.map[(int)(t_c3d.plyr_y / SZ_PX)][(int)(t_c3d.plyr_x / SZ_PX)] == '2')
			{
				t_cr_sprt.x = (int)(t_c3d.plyr_x / SZ_PX) * SZ_PX + (SZ_PX / 2);
				t_cr_sprt.y = (int)(t_c3d.plyr_y / SZ_PX) * SZ_PX + (SZ_PX / 2);
			}
			if (t_c3d.map[(int)(t_c3d.plyr_y / SZ_PX)][(int)(t_c3d.plyr_x / SZ_PX)] == '1'
			||
			(t_c3d.map[(int)((t_c3d.plyr_y - 1) / SZ_PX)][(int)((t_c3d.plyr_x + 1)/ SZ_PX)] == '1'
			&& t_c3d.map[(int)((t_c3d.plyr_y + 1) / SZ_PX)][(int)((t_c3d.plyr_x - 1)/ SZ_PX)] == '1')
			||
			(t_c3d.map[(int)((t_c3d.plyr_y - 1) / SZ_PX)][(int)((t_c3d.plyr_x - 1)/ SZ_PX)] == '1'
			&& t_c3d.map[(int)((t_c3d.plyr_y + 1) / SZ_PX)][(int)((t_c3d.plyr_x + 1)/ SZ_PX)] == '1')||
			(t_c3d.map[(int)((t_c3d.plyr_y - 1) / SZ_PX)][(int)((t_c3d.plyr_x + 1)/ SZ_PX)] == '1'
			 && t_c3d.map[(int)((t_c3d.plyr_y + 1) / SZ_PX)][(int)((t_c3d.plyr_x - 1)/ SZ_PX)] == '1')
			||
			(t_c3d.map[(int)((t_c3d.plyr_y - 1) / SZ_PX)][(int)((t_c3d.plyr_x - 1)/ SZ_PX)] == '1'
			 && t_c3d.map[(int)((t_c3d.plyr_y + 1) / SZ_PX)][(int)((t_c3d.plyr_x + 1)/ SZ_PX)] == '1')
			)
				break;
		}
		draw_t(img, t_c3d.cf_rcs, xx++);
		t_c3d.cf_rcs = 0;
		t_c3d.crnr_s += (M_PI/3)/t_c3d.x_r;
		step += (M_PI/3)/t_c3d.x_r;
	}






	x = 0;
	y = 0;
	while ((t_c3d.map)[y])
	{
		while ((t_c3d.map)[y][x])
		{
			if ((t_c3d.map)[y][x] == '1')
				put_map(x, y, 0xffffff, SZ_PX/8, img);
			else if ((t_c3d.map)[y][x] == '2')
				put_map(x, y, 0x75c1ff, SZ_PX/8, img);
			else if (ft_strchr("NSEW", (t_c3d.map)[y][x]) && !t_c3d.orien)
			{
				t_c3d.orien = (t_c3d.map)[y][x];
				img->strt_x = x * SZ_PX + (SZ_PX / 2);
				img->strt_y = y * SZ_PX + (SZ_PX / 2);
			}
			x++;
		}
		x = 0;
		y++;
	}
	printf("x : %d\n", xx);
	draw_sprite(img);
	mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img->img, 0, 0);
}
