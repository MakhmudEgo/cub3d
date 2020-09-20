/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:59:17 by mizola            #+#    #+#             */
/*   Updated: 2020/09/15 20:22:29 by mizola           ###   ########.fr       */
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

	dst = data->addr + ((y * data->h_xpm/64) * data->l_len + x * (data->bpp / 8));
	return (*(unsigned int*)dst);
}

int		vget_xpm_color(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + ((y + (data->h_xpm / 64)) * data->l_len - (x+1) * (data->bpp / 8));
	return (*(unsigned int*)dst);
}

/*double get_cff(t_data *data)
{
	return 2.2;
}*/

void draw_wall(t_data *data, double lv, int x)
{
	lv *= cos(data->crnr - data->crnr_s);
	int start = data->y_r / 2 - (data->y_r / lv * SZ_PX) / 2;
	int end = data->y_r / 2 + (data->y_r / lv * SZ_PX) / 2;
	double cff_ea = (double)data->txtr_ea.h_xpm / (end - start);
	double cff_we = (double)data->txtr_we.h_xpm / (end - start);
	double cff_so = (double)data->txtr_we.h_xpm / (end - start);
	double cff_no = (double)data->txtr_we.h_xpm / (end - start);
	int tmp = start;
	while (start < end && start < data->y_r)//
	{
		if (start >= 0)
		{
			if (data->map[(int)(data->plyr_y) / SZ_PX][(int)(data->plyr_x - 0.25 * cos(data->crnr_s)) / SZ_PX] == '1')
			{
				if (data->map[(int)(data->plyr_y + 32) / SZ_PX][(int)(data->plyr_x) / SZ_PX] == '1')
					my_mlx_pixel_put(&data->img, x, start, get_xpm_color(&data->txtr_so, (int)data->plyr_x * (data->txtr_so.w_xpm / SZ_PX) % data->txtr_so.w_xpm, (int)((start - tmp) * cff_so)));
				else
					my_mlx_pixel_put(&data->img, x, start, vget_xpm_color(&data->txtr_no, (int)data->plyr_x * (data->txtr_no.w_xpm / SZ_PX) % data->txtr_no.w_xpm, (int)((start - tmp) * cff_no)));
			}
			else
			{
				if (data->map[(int)(data->plyr_y) / SZ_PX][(int)(data->plyr_x + 32) / SZ_PX] == '1')
					my_mlx_pixel_put(&data->img, x, start, vget_xpm_color(&data->txtr_ea, (int)data->plyr_y * (data->txtr_ea.w_xpm / SZ_PX) % data->txtr_ea.h_xpm, (int)((start - tmp) * cff_ea)));
				else
					my_mlx_pixel_put(&data->img, x, start, get_xpm_color(&data->txtr_we, (int)data->plyr_y * (data->txtr_we.w_xpm / SZ_PX) % data->txtr_we.h_xpm, (int)((start - tmp) * cff_we)));
			}
		}
		start++;
	}
}
//--------------------------------------sprite----------------------------
void draw_sprite(void **sprites, t_data *data, const double *stn, int n)
{
	// абсолютное направление от игрока до спрайта (в радианах)
	while (0 <= n)
	{
		double sprite_dir = atan2(((t_coors *)(sprites[n]))->y - data->strt_y, ((t_coors *)(sprites[n]))->x - data->strt_x);
		// удаление лишних оборотов
		while (sprite_dir - data->crnr > M_PI) sprite_dir -= 2 * M_PI;
		while (sprite_dir - data->crnr < -M_PI) sprite_dir += 2 * M_PI;

		// расстояние от игрока до спрайта
		double sprite_dist = ((t_coors *)(sprites[n]))->l_len; //sqrt(pow(img->strt_x - t_cr_sprt.x, 2) + pow(img->strt_y - t_cr_sprt.y, 2));
		int sprite_screen_size = data->y_r / sprite_dist * 64;
		// не забывайте, что 3D вид занимает только половину кадрового буфера,
		// таким образом, fb.w/2 для ширины экрана
		int h_offset = (sprite_dir - data->crnr) * (data->x_r) / (M_PI / 3) + (data->x_r / 2) - sprite_screen_size / 2;
		int v_offset = data->y_r / 2 - sprite_screen_size / 2;

		int color;
		int i = -1;
		int j = -1;
		while (++i < sprite_screen_size) {
			j = -1;
			if (h_offset+ i <0 || h_offset+i>=data->x_r)
				continue;
			if (stn[h_offset + i] < sprite_dist)
				continue;
			while (++j < sprite_screen_size) {
				if (v_offset+ j < 0 || v_offset+j >= data->y_r)
					continue;
				int x = i * ((double) data->txtr_sp.w_xpm / (double) sprite_screen_size);
				int y = j * ((double) data->txtr_sp.h_xpm / (double) sprite_screen_size);
				color = *(unsigned int *) (data->txtr_sp.addr + (y * data->txtr_sp.l_len + x * (data->txtr_sp.bpp / 8)));
				if ((h_offset + i >= 0 && h_offset + i < data->x_r) &&
					(v_offset + j >= 0 && v_offset + j < data->y_r) && color > 0)
					my_mlx_pixel_put(&data->img, h_offset + i, v_offset + j, color);
			}
		}
		n--;
	}
}

void  sp_sortlst(t_coors *sprts, void **arr)
{
	int		i;
	int		j;
	int		n;

	i = 0;
	while (sprts && sprts->next)
	{
		arr[i] = sprts;
		sprts = sprts->next;
		i++;
	}
	arr[i] = sprts;
	n = i + 1;
	i = 1;
	j = 0;
	while (i < n) {
		while (j < n - 1) {
			if (((t_coors *)(arr[j]))->l_len > ((t_coors *)(arr[j+1]))->l_len)
			{
				void *tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;
			}
			j++;
		}
		j = 0;
		i++;
	}
}

static void get_len_sprts(t_data *data)
{
	t_coors *sprts = data->sprts;
	while (data->sprts->next)
	{
		data->sprts->l_len = sqrt(pow(data->strt_x - data->sprts->x, 2) + pow(data->strt_y - data->sprts->y, 2));
		data->sprts = data->sprts->next;
	}
	data->sprts->l_len = sqrt(pow(data->strt_x - data->sprts->x, 2) + pow(data->strt_y - data->sprts->y, 2));
	data->sprts = sprts;
}
//--------------------------------------sprite----------------------------

void    parse_map(t_data *data)
{
    int y;
    int x;

    y = 0;
    x = 0;
	data->img.img = mlx_new_image(data->mlx.mlx, data->x_r, data->y_r);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.l_len, &data->img.endian);
	while (y < data->y_r / 2)
	{
		my_mlx_pixel_put(&data->img, x, y, data->c_t);//0xffd1d8
		if (x == data->x_r && y < data->y_r - 1)
		{
			x = 0;
			y++;
		}
		x++;
	}
	x = 0;
	while (y < data->y_r)
	{
		my_mlx_pixel_put(&data->img, x, y, data->f_t);//0x75c1ff
		if (x == data->x_r && y < data->y_r)
		{
			x = 0;
			y++;
		}
		x++;
	}
	x = 0;
	y = 0;
    while ((data->map)[y])
    {
        while ((data->map)[y][x])
        {
            if (ft_strchr("NSEW", (data->map)[y][x]) && !data->orien)
            {
            	data->orien = (data->map)[y][x];
                data->strt_x = x * SZ_PX + (SZ_PX / 2);
				data->strt_y = y * SZ_PX + (SZ_PX / 2);
			}
			x++;
        }
		x = 0;
		y++;
	}
	int vrtl_line = 0;
    double step = 0;
	double stn[data->x_r];
	while (step < M_PI / 3)
	{
		while (GAME)
		{
			data->plyr_x = data->strt_x + data->cf_rcs * cos(data->crnr_s);
			data->plyr_y = data->strt_y + data->cf_rcs * sin(data->crnr_s);
			data->cf_rcs += 0.25;
			if (data->map[(int)(data->plyr_y / SZ_PX)][(int)(data->plyr_x / SZ_PX)] == '1'
			||
			(data->map[(int)((data->plyr_y - 1) / SZ_PX)][(int)((data->plyr_x + 1)/ SZ_PX)] == '1'
			&& data->map[(int)((data->plyr_y + 1) / SZ_PX)][(int)((data->plyr_x - 1)/ SZ_PX)] == '1')
			||
			(data->map[(int)((data->plyr_y - 1) / SZ_PX)][(int)((data->plyr_x - 1)/ SZ_PX)] == '1'
			&& data->map[(int)((data->plyr_y + 1) / SZ_PX)][(int)((data->plyr_x + 1)/ SZ_PX)] == '1')
			)
				break;
		}
		stn[vrtl_line] = data->cf_rcs;
		draw_wall(data, data->cf_rcs, vrtl_line++);
		data->cf_rcs = 0;
		data->crnr_s += (M_PI/3)/data->x_r;
		step += (M_PI/3)/data->x_r;
	}
	get_len_sprts(data);
	if (!data->init_sp)
		data->sprites = malloc(sizeof(void *) * sp_lstsize(data->sprts));
	data->init_sp = 1;
	sp_sortlst(data->sprts, data->sprites);
	draw_sprite(data->sprites, data, stn, sp_lstsize(data->sprts) - 1);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.wnd, data->img.img, 0, 0);
}
