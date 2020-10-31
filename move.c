/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:02:47 by mizola            #+#    #+#             */
/*   Updated: 2020/09/20 18:02:49 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_up_and_down(int key, t_data *data)
{
	if (UP)
	{
		if ((data->map)[(int)(data->strt_y + sin(data->crnr) * 21) / SZ_PX]
		[(int)(data->strt_x + cos(data->crnr) * 21) / SZ_PX] != '1')
		{
			data->strt_x += cos(data->crnr) * 21;
			data->strt_y += sin(data->crnr) * 21;
			data->crnr_s = data->crnr - M_PI_6;
			parse_map(data);
		}
	}
	if (DOWN)
	{
		if ((data->map)[(int)(data->strt_y - sin(data->crnr) * 21) / SZ_PX]
		[(int)(data->strt_x - cos(data->crnr) * 21) / SZ_PX] != '1')
		{
			data->strt_x -= cos(data->crnr) * 21;
			data->strt_y -= sin(data->crnr) * 21;
			data->crnr_s = data->crnr - M_PI_6;
			parse_map(data);
		}
	}
}

static void	move_right_and_left(int key, t_data *data)
{
	if (LEFT)
	{
		if ((data->map)[(int)(data->strt_y - cos(data->crnr) * 21) / SZ_PX]
		[(int)(data->strt_x + sin(data->crnr) * 21) / SZ_PX] != '1')
		{
			data->strt_x += sin(data->crnr) * 21;
			data->strt_y -= cos(data->crnr) * 21;
			data->crnr_s = data->crnr - M_PI_6;
			parse_map(data);
		}
	}
	if (RIGHT)
	{
		if ((data->map)[(int)(data->strt_y + cos(data->crnr) * 21) / SZ_PX]
		[(int)(data->strt_x - sin(data->crnr) * 21) / SZ_PX] != '1')
		{
			data->strt_x -= sin(data->crnr) * 21;
			data->strt_y += cos(data->crnr) * 21;
			data->crnr_s = data->crnr - M_PI_6;
			parse_map(data);
		}
	}
}

int			move(int key, t_data *data)
{
	if (DOWN || UP)
		move_up_and_down(key, data);
	if (LEFT || RIGHT)
		move_right_and_left(key, data);
	if (L_RT)
	{
		data->crnr += (data->crnr - 0.3 < 0) ? M_PI * 2 - 0.3 : -0.3;
		data->crnr_s = data->crnr - M_PI_6;
		parse_map(data);
	}
	if (R_RT)
	{
		data->crnr += (data->crnr + 0.3 > M_PI * 2) ? -data->crnr + 0.3 : 0.3;
		data->crnr_s = data->crnr - M_PI_6;
		parse_map(data);
	}
	if (key == 0x35)
		exit(0);
	return (1);
}
