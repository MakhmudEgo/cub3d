/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_data_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 11:23:44 by mizola            #+#    #+#             */
/*   Updated: 2020/09/21 11:23:45 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sp_data_init(t_sp_data *data)
{
	data->sp_dr = 0x0;
	data->sp_dist = 0x0;
	data->sp_scrn_sz = 0x0;
	data->h_off = 0x0;
	data->v_off = 0x0;
	data->clr = 0x0;
	data->i = 0x0;
	data->j = 0x0;
	data->x = 0x0;
	data->y = 0x0;
}
