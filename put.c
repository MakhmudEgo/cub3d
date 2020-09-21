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

void		my_pxl_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int			get_xpm_clr(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + ((y * data->h_xpm / 64)
	* data->l_len + x * (data->bpp / 8));
	return (*(int*)dst);
}

int			vget_xpm_color(t_img *data, int x, int y)
{
	char	*dst;

	dst = data->addr + ((y + (data->h_xpm / 64))
	* data->l_len - (x + 1) * (data->bpp / 8));
	return (*(int*)dst);
}

int			get_y(t_img *txtr, int start, int end, t_data *data)
{
	int tmp;

	tmp = data->y_r / 2 - (data->y_r / data->cf_rcs * SZ_PX) / 2;
	return ((int)((start - tmp) * (double)txtr->h_xpm / (end - tmp)));
}

static void	draw_wall_ass(t_data *data, int x, int start, int end)
{
	if (start >= 0 && data->map[(int)(data->plyr_y) / SZ_PX]
	[(int)(data->plyr_x - 0.25 * cos(data->crnr_s)) / SZ_PX] == '1')
	{
		if (data->map[(int)(data->plyr_y + 32) / SZ_PX]
		[(int)(data->plyr_x) / SZ_PX] == '1')
			my_pxl_put(&data->img, x, start, get_xpm_clr(&data->txtr_so,
			(int)data->plyr_x * (data->txtr_so.w_xpm / SZ_PX) %
			data->txtr_so.w_xpm, get_y(&data->txtr_so, start, end, data)));
		else
			my_pxl_put(&data->img, x, start, vget_xpm_color(&data->txtr_no,
			(int)data->plyr_x * (data->txtr_no.w_xpm / SZ_PX) %
			data->txtr_no.w_xpm, get_y(&data->txtr_no, start, end, data)));
	}
	else if (start >= 0)
	{
		if (data->map[(int)(data->plyr_y) / SZ_PX]
		[(int)(data->plyr_x + 32) / SZ_PX] == '1')
			my_pxl_put(&data->img, x, start, vget_xpm_color(&data->txtr_ea,
			(int)data->plyr_y * (data->txtr_ea.w_xpm / SZ_PX) %
			data->txtr_ea.h_xpm, get_y(&data->txtr_ea, start, end, data)));
		else
			my_pxl_put(&data->img, x, start, get_xpm_clr(&data->txtr_we,
			(int)data->plyr_y * (data->txtr_we.w_xpm / SZ_PX) %
			data->txtr_we.h_xpm, get_y(&data->txtr_we, start, end, data)));
	}
}

void		draw_wall(t_data *data, int x)
{
	int start;
	int end;

	data->cf_rcs *= cos(data->crnr - data->crnr_s);
	start = data->y_r / 2 - (data->y_r / data->cf_rcs * SZ_PX) / 2;
	end = data->y_r / 2 + (data->y_r / data->cf_rcs * SZ_PX) / 2;
	while (start < end && start < data->y_r)
	{
		draw_wall_ass(data, x, start, end);
		start++;
	}
}

void		draw_sprite_ass(t_sp_data *sp_data, t_data *data)
{
	while (++sp_data->j < sp_data->sp_scrn_sz)
	{
		if (sp_data->v_off + sp_data->j < 0
		|| sp_data->v_off + sp_data->j >= data->y_r)
			continue;
		sp_data->x = sp_data->i * ((double)data->txtr_sp.w_xpm
		/ (double)sp_data->sp_scrn_sz);
		sp_data->y = sp_data->j * ((double)data->txtr_sp.h_xpm
		/ (double)sp_data->sp_scrn_sz);
		sp_data->clr = *(int *)(data->txtr_sp.addr + (sp_data->y *
		data->txtr_sp.l_len + sp_data->x * (data->txtr_sp.bpp / 8)));
		if ((sp_data->h_off + sp_data->i >= 0 && sp_data->h_off + sp_data->i <
		data->x_r) && (sp_data->v_off + sp_data->j >= 0 && sp_data->v_off
		+ sp_data->j < data->y_r) && sp_data->clr > 0)
			my_pxl_put(&data->img, sp_data->h_off + sp_data->i,
			sp_data->v_off + sp_data->j, sp_data->clr);
	}
}

void		draw_sprite_as(t_sp_data *sp_data, t_data *data, const double *stn)
{
	while (++sp_data->i < sp_data->sp_scrn_sz)
	{
		sp_data->j = -1;
		if (sp_data->h_off + sp_data->i < 0
		|| sp_data->h_off + sp_data->i >= data->x_r)
			continue;
		if (stn[sp_data->h_off + sp_data->i] < sp_data->sp_dist)
			continue;
		draw_sprite_ass(sp_data, data);
	}
}

void		draw_sprite(void **sprites, t_data *data, const double *stn, int n)
{
	t_sp_data sp_data;

	while (0 <= n)
	{
		sp_data.sp_dr = atan2(((t_coors *)(sprites[n]))->y - data->strt_y,
		((t_coors *)(sprites[n]))->x - data->strt_x);
		while (sp_data.sp_dr - data->crnr > M_PI)
			sp_data.sp_dr -= 2 * M_PI;
		while (sp_data.sp_dr - data->crnr < -M_PI)
			sp_data.sp_dr += 2 * M_PI;
		sp_data.sp_dist = ((t_coors *)(sprites[n]))->l_len;
		sp_data.sp_scrn_sz = data->y_r / sp_data.sp_dist * 64;
		sp_data.h_off = (sp_data.sp_dr - data->crnr) * (data->x_r)
		/ (M_PI / 3) + (data->x_r / 2) - sp_data.sp_scrn_sz / 2;
		sp_data.v_off = data->y_r / 2 - sp_data.sp_scrn_sz / 2;
		sp_data.i = -1;
		draw_sprite_as(&sp_data, data, stn);
		n--;
	}
}

void		sort_arr_sprt(void **arr, int n)
{
	int		i;
	int		j;
	void	*tmp;

	i = 0;
	j = -1;
	tmp = 0x0;
	while (++i < n)
	{
		while (++j < n - 1)
		{
			if (((t_coors *)(arr[j]))->l_len > ((t_coors *)(arr[j + 1]))->l_len)
			{
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
		j = -1;
	}
}

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

static void	get_len_sprts(t_data *data)
{
	t_coors *sprts;

	sprts = data->sprts;
	while (data->sprts->next)
	{
		data->sprts->l_len = sqrt(pow(data->strt_x - data->sprts->x, 2)
		+ pow(data->strt_y - data->sprts->y, 2));
		data->sprts = data->sprts->next;
	}
	data->sprts->l_len = sqrt(pow(data->strt_x - data->sprts->x, 2)
	+ pow(data->strt_y - data->sprts->y, 2));
	data->sprts = sprts;
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
