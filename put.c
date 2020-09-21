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

void		sp_sortlst(t_coors *sprts, void **arr)
{
	int		i;

	i = -1;
	while (sprts && sprts->next)
	{
		arr[++i] = sprts;
		sprts = sprts->next;
	}
	arr[++i] = sprts;
	sort_arr_sprt(arr, i + 1);
}

void		wall_fc(t_data *data)
{
	int y;
	int x;

	y = 0;
	x = 0;
	while (y < data->y_r / 2)
	{
		my_pxl_put(&data->img, x, y, data->c_t);
		if (x == data->x_r && y < data->y_r - 1)
		{
			x = 0;
			y++;
		}
		x++;
	}
	x = -1;
	while (y < data->y_r)
	{
		while (++x < data->x_r)
			my_pxl_put(&data->img, x, y, data->f_t);
		x = -1;
		y++;
	}
}

void		raycasting_ass(t_data *data)
{
	while (GAME)
	{
		data->plyr_x = data->strt_x + data->cf_rcs * cos(data->crnr_s);
		data->plyr_y = data->strt_y + data->cf_rcs * sin(data->crnr_s);
		data->cf_rcs += 0.25;
		if (data->map[(int)(data->plyr_y / SZ_PX)]
		[(int)(data->plyr_x / SZ_PX)] == '1'
		|| (data->map[(int)((data->plyr_y - 1) / SZ_PX)]
		[(int)((data->plyr_x + 1) / SZ_PX)] == '1'
		&& data->map[(int)((data->plyr_y + 1) / SZ_PX)]
		[(int)((data->plyr_x - 1) / SZ_PX)] == '1')
		|| (data->map[(int)((data->plyr_y - 1) / SZ_PX)]
		[(int)((data->plyr_x - 1) / SZ_PX)] == '1'
		&& data->map[(int)((data->plyr_y + 1) / SZ_PX)]
		[(int)((data->plyr_x + 1) / SZ_PX)] == '1'))
			break ;
	}
}

void		raycasting(t_data *data, double *stn)
{
	int		vrtl_line;
	double	step;

	vrtl_line = 0;
	step = 0;
	while (step < M_PI / 3)
	{
		raycasting_ass(data);
		stn[vrtl_line] = data->cf_rcs;
		draw_wall(data, vrtl_line++);
		data->cf_rcs = 0;
		data->crnr_s += (M_PI / 3) / data->x_r;
		step += (M_PI / 3) / data->x_r;
	}
}

void		parse_map(t_data *data)
{
	double stn[data->x_r];

	mlx_destroy_image(data->mlx.mlx, data->img.img);
	data->img.img = mlx_new_image(data->mlx.mlx, data->x_r, data->y_r);
	!data->img.img ? exit_notify("No Image\n", 49) : 0;
	data->img.addr = mlx_get_data_addr(data->img.img,
	&data->img.bpp, &data->img.l_len, &data->img.endian);
	wall_fc(data);
	raycasting(data, stn);
	get_len_sprts(data);
	if (!data->init_sp)
		data->sprites = malloc(sizeof(void *) * sp_lstsize(data->sprts));
	data->init_sp = 1;
	sp_sortlst(data->sprts, data->sprites);
	draw_sprite(data->sprites, data, stn, sp_lstsize(data->sprts) - 1);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.wnd, data->img.img, 0, 0);
	if (data->scrn)
	{
		save_screen(data);
		exit(41);
	}
}
