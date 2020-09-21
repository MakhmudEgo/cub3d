/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 10:52:05 by mizola            #+#    #+#             */
/*   Updated: 2020/09/21 10:52:11 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_scrn_sz(t_data *data, char *s)
{
	is_valid_data(++s, ' ', 2, "screen size ko\n");
	data->x_r = ft_atoi(s);
	while (s && *s == ' ' && *s != '\0')
		s++;
	while (s && *s != ' ' && *s != '\0')
		s++;
	data->y_r = ft_atoi(s);
	mlx_get_screen_size(data->mlx.mlx, &data->x_mx, &data->y_mx);
	data->x_r > data->x_mx ? data->x_r = data->x_mx : 0;
	data->y_r > data->y_mx ? data->y_r = data->y_mx : 0;
}

int			create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
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

void		my_pxl_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}
