/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 11:03:56 by mizola            #+#    #+#             */
/*   Updated: 2020/09/21 11:03:57 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
