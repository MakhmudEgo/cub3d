/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:53:39 by mizola            #+#    #+#             */
/*   Updated: 2020/08/23 16:24:01 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_len + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int		start(int key, t_data *data)
{
	short x_u = (data->strt_x + cos(data->crnr) * 4);
	short y_u = (data->strt_y + sin(data->crnr) * 4);
	short x_d = (data->strt_x - cos(data->crnr) * 4);
	short y_d = (data->strt_y - sin(data->crnr) * 4);
	if (UP)
	{
		if ((data->map)[y_u / SZ_PX][x_u / SZ_PX] != '1')
		{
			data->strt_x += cos(data->crnr) * 4;
			data->strt_y += sin(data->crnr) * 4;
			data->crnr_s = data->crnr - M_PI_6;
			parse_map(data);
		}
	}
	if (DOWN)
	{
		if ((data->map)[y_d / SZ_PX][x_d / SZ_PX] != '1')
		{
			data->strt_x -= cos(data->crnr) * 4;
			data->strt_y -= sin(data->crnr) * 4;
			data->crnr_s = data->crnr - M_PI_6;
			parse_map(data);
		}
	}
	if (LEFT)
	{
		if ((data->map)[(int)(data->strt_y - cos(data->crnr) * 4)/ SZ_PX][(int)(data->strt_x + sin(data->crnr) * 4) / SZ_PX] != '1')
		{
			data->strt_x += sin(data->crnr) * 4;
			data->strt_y -= cos(data->crnr) * 4;
			data->crnr_s = data->crnr - M_PI_6;
			parse_map(data);
		}
	}
	if (RIGHT)
	{
		if ((data->map)[(int)(data->strt_y + cos(data->crnr) * 4)/ SZ_PX][(int)(data->strt_x - sin(data->crnr) * 4) / SZ_PX] != '1')
		{
			data->strt_x -= sin(data->crnr) * 4;
			data->strt_y += cos(data->crnr) * 4;
			data->crnr_s = data->crnr - M_PI_6;
			parse_map(data);
		}
	}
	if (L_RT)
	{
		data->crnr += (data->crnr - 0.2 < 0) ? M_PI * 2 - 0.2 : -0.2;
		data->crnr_s = data->crnr - M_PI_6;
		parse_map(data);
	}
	if (R_RT)
	{
		data->crnr += (data->crnr + 0.2 > M_PI * 2) ? -data->crnr + 0.2 : 0.2;
		data->crnr_s = data->crnr - M_PI_6;
		parse_map(data);
	}
	if (key == 0x35)
		exit(123);
	return 1;
}

void	txtr_init(t_data *data)
{
	data->txtr_ea.img = mlx_xpm_file_to_image(data->mlx.mlx, data->ea_t, &data->txtr_ea.w_xpm, &data->txtr_ea.h_xpm);
	data->txtr_no.img = mlx_xpm_file_to_image(data->mlx.mlx, data->no_t, &data->txtr_no.w_xpm, &data->txtr_no.h_xpm);
	data->txtr_so.img = mlx_xpm_file_to_image(data->mlx.mlx, data->so_t, &data->txtr_so.w_xpm, &data->txtr_so.h_xpm);
	data->txtr_we.img = mlx_xpm_file_to_image(data->mlx.mlx, data->we_t, &data->txtr_we.w_xpm, &data->txtr_we.h_xpm);
	data->txtr_sp.img = mlx_xpm_file_to_image(data->mlx.mlx, data->sp_t, &data->txtr_sp.w_xpm, &data->txtr_sp.h_xpm);
	if (data->txtr_ea.img && data->txtr_no.img && data->txtr_so.img && data->txtr_we.img && data->txtr_sp.img)
	{
		data->txtr_ea.addr = mlx_get_data_addr(data->txtr_ea.img, &data->txtr_ea.bpp, &data->txtr_ea.l_len, &data->txtr_ea.endian);
		data->txtr_no.addr = mlx_get_data_addr(data->txtr_no.img, &data->txtr_no.bpp, &data->txtr_no.l_len, &data->txtr_no.endian);
		data->txtr_so.addr = mlx_get_data_addr(data->txtr_so.img, &data->txtr_so.bpp, &data->txtr_so.l_len, &data->txtr_so.endian);
		data->txtr_we.addr = mlx_get_data_addr(data->txtr_we.img, &data->txtr_we.bpp, &data->txtr_we.l_len, &data->txtr_we.endian);
		data->txtr_sp.addr = mlx_get_data_addr(data->txtr_sp.img, &data->txtr_sp.bpp, &data->txtr_sp.l_len, &data->txtr_sp.endian);
	}
	else
		exit_notify("texture file ko\n", 45);

}

void check_arg_exp(char **s, int argc, t_data *data)
{
	if (argc == 3)
		(!ft_strncmp(s[1], s[2], 6) ||  ft_strlen(s[2]) != 6) ? exit_notify("No valid argv\n", 77) : 0;
	if ((ft_strlen(s[1]) < 5) || ft_strncmp(&s[1][ft_strlen(s[1]) - 4], ".cub", 4))
		exit_notify("No valid exp .cub\n", 55);
	data->scrn = argc == 3 ? 1 : 0;
}

int main(int argc, char **argv)
{
	t_data data;

	(argc < 2 || argc > 3) ? exit_notify("No valid argc\n", 55) : check_arg_exp(argv, argc, &data);
	prs_cub3d(argv[1], &data) ? exit_notify("No valid arg\n", 55) : 0;
	data.mlx.mlx = mlx_init();
	txtr_init(&data);
	data.mlx.wnd = mlx_new_window(data.mlx.mlx, data.x_r, data.y_r, "cub3d");
	!(data.img.img = mlx_new_image(data.mlx.mlx, data.x_r, data.y_r)) ? exit_notify("No Image\n", 11) : 0;
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.l_len, &data.img.endian);
	parse_map(&data);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.wnd, data.img.img, 0, 0);
	mlx_hook(data.mlx.wnd, 2, 0L, start, &data);
    mlx_loop(data.mlx.mlx);
	return (0);
}
