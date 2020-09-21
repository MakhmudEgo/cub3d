/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 11:08:36 by mizola            #+#    #+#             */
/*   Updated: 2020/09/21 11:08:37 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void		draw_sprite_ass(t_sp_data *sp_data, t_data *data)
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

static void		draw_sprite_as(t_sp_data *sp_data,
				t_data *data, const double *stn)
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

void			sort_arr_sprt(void **arr, int n)
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

void			get_len_sprts(t_data *data)
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

void			draw_sprite(void **sprites, t_data *data,
				const double *stn, int n)
{
	t_sp_data sp_data;

	sp_data_init(&sp_data);
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
