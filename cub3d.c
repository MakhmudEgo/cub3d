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
	short x_u = (data->img.strt_x + cos(t_c3d.crnr) * 4);
	short y_u = (data->img.strt_y + sin(t_c3d.crnr) * 4);
	short x_d = (data->img.strt_x - cos(t_c3d.crnr) * 4);
	short y_d = (data->img.strt_y - sin(t_c3d.crnr) * 4);
	if (UP)
	{
		if ((t_c3d.map)[y_u / SZ_PX][x_u / SZ_PX] != '1')
		{
			data->img.strt_x += cos(t_c3d.crnr) * 4;
			data->img.strt_y += sin(t_c3d.crnr) * 4;
			t_c3d.crnr_s = t_c3d.crnr - M_PI_6;
			parse_map(data);
		}
	}
	if (DOWN)
	{
		if ((t_c3d.map)[y_d / SZ_PX][x_d / SZ_PX] != '1')
		{
			data->img.strt_x -= cos(t_c3d.crnr) * 4;
			data->img.strt_y -= sin(t_c3d.crnr) * 4;
			t_c3d.crnr_s = t_c3d.crnr - M_PI_6;
			parse_map(data);
		}
	}
	if (LEFT)
	{
		if ((t_c3d.map)[(int)(data->img.strt_y - cos(t_c3d.crnr) * 4)/ SZ_PX][(int)(data->img.strt_x + sin(t_c3d.crnr) * 4) / SZ_PX] != '1')
		{
			data->img.strt_x += sin(t_c3d.crnr) * 4;
			data->img.strt_y -= cos(t_c3d.crnr) * 4;
			t_c3d.crnr_s = t_c3d.crnr - M_PI_6;
			parse_map(data);
		}
	}
	if (RIGHT)
	{
		if ((t_c3d.map)[(int)(data->img.strt_y + cos(t_c3d.crnr) * 4)/ SZ_PX][(int)(data->img.strt_x - sin(t_c3d.crnr) * 4) / SZ_PX] != '1')
		{
			data->img.strt_x -= sin(t_c3d.crnr) * 4;
			data->img.strt_y += cos(t_c3d.crnr) * 4;
			t_c3d.crnr_s = t_c3d.crnr - M_PI_6;
			parse_map(data);
		}
	}
	if (L_RT)
	{
		t_c3d.crnr += (t_c3d.crnr - 0.2 < 0) ? M_PI * 2 - 0.2 : -0.2;
		t_c3d.crnr_s = t_c3d.crnr - M_PI_6;
		t_c3d.crnr_e = t_c3d.crnr + M_PI_6;
		parse_map(data);
	}
	if (R_RT)
	{
		t_c3d.crnr += (t_c3d.crnr + 0.2 > M_PI * 2) ? -t_c3d.crnr + 0.2 : 0.2;
		t_c3d.crnr_s = t_c3d.crnr - M_PI_6;
		t_c3d.crnr_e = t_c3d.crnr + M_PI_6;
		parse_map(data);
	}
	printf("key == %#x\n", key);
	if (key == 0x35)
		exit(123);
	return 1;
}

void	txtr_init(t_data *data)
{
	data->txtr_ea.img = mlx_xpm_file_to_image(data->mlx.mlx, t_c3d.ea_t, &data->txtr_ea.w_xpm, &data->txtr_ea.h_xpm);
	data->txtr_ea.addr = mlx_get_data_addr(data->txtr_ea.img, &data->txtr_ea.bpp, &data->txtr_ea.l_len, &data->txtr_ea.endian);

	data->txtr_no.img = mlx_xpm_file_to_image(data->mlx.mlx, t_c3d.no_t, &data->txtr_no.w_xpm, &data->txtr_no.h_xpm);
	data->txtr_no.addr = mlx_get_data_addr(data->txtr_no.img, &data->txtr_no.bpp, &data->txtr_no.l_len, &data->txtr_no.endian);

	data->txtr_so.img = mlx_xpm_file_to_image(data->mlx.mlx, t_c3d.so_t, &data->txtr_so.w_xpm, &data->txtr_so.h_xpm);
	data->txtr_so.addr = mlx_get_data_addr(data->txtr_so.img, &data->txtr_so.bpp, &data->txtr_so.l_len, &data->txtr_so.endian);

	data->txtr_we.img = mlx_xpm_file_to_image(data->mlx.mlx, t_c3d.we_t, &data->txtr_we.w_xpm, &data->txtr_we.h_xpm);
	data->txtr_we.addr = mlx_get_data_addr(data->txtr_we.img, &data->txtr_we.bpp, &data->txtr_we.l_len, &data->txtr_we.endian);

	data->txtr_sp.img = mlx_xpm_file_to_image(data->mlx.mlx, t_c3d.sp_t, &data->txtr_sp.w_xpm, &data->txtr_sp.h_xpm);
	data->txtr_sp.addr = mlx_get_data_addr(data->txtr_sp.img, &data->txtr_sp.bpp, &data->txtr_sp.l_len, &data->txtr_sp.endian);

}

void check_arg_exp(char **s, int argc)
{
	if (argc == 3)
		(!ft_strncmp(s[1], s[2], 6) ||  ft_strlen(s[2]) != 6) ? exit(77) : write(1, "exp norm!\n", 10);
//	ft_strnstr()
	printf("фисё окк\n");
}

int main(int argc, char **argv)
{
	t_data data;

	(argc < 2 || argc > 3) ? exit(45) : check_arg_exp(argv, argc);
	(prs_cub3d(argv[1], &data.sprts) ? exit(55) : write(1, "фисе ок1\n", 9));

	data.mlx.mlx = mlx_init();
	txtr_init(&data);
	data.mlx.wnd = mlx_new_window(data.mlx.mlx, t_c3d.x_r, t_c3d.y_r, "cub3d");
	data.img.img = mlx_new_image(data.mlx.mlx, t_c3d.x_r, t_c3d.y_r);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.l_len, &data.img.endian);
	parse_map(&data);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.wnd, data.img.img, 0, 0);
	mlx_hook(data.mlx.wnd, 2, 0L, start, &data);
    mlx_loop(data.mlx.mlx);
	return (0);
}
