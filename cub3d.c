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

int		start(int key, t_img *img, t_coors *sprts, s_data *data)
{
	short x_u = (img->strt_x + cos(t_c3d.crnr) * 4);// + t_c3d.cf_rcs * cos(t_c3d.crnr_s);
	short y_u = (img->strt_y + sin(t_c3d.crnr) * 4);// + t_c3d.cf_rcs * sin(t_c3d.crnr_s);
	short x_d = (img->strt_x - cos(t_c3d.crnr) * 4);// + t_c3d.cf_rcs * cos(t_c3d.crnr_s);
	short y_d = (img->strt_y - sin(t_c3d.crnr) * 4);// + t_c3d.cf_rcs * sin(t_c3d.crnr_s);
	if (UP)
	{
		if ((t_c3d.map)[y_u / SZ_PX][x_u / SZ_PX] != '1')
		{
			img->strt_x += cos(t_c3d.crnr) * 4;
			img->strt_y += sin(t_c3d.crnr) * 4;
			t_c3d.crnr_s = t_c3d.crnr - M_PI_6;
			parse_map(img, sprts, data);
		}
	}
	if (DOWN)
	{
		if ((t_c3d.map)[y_d / SZ_PX][x_d / SZ_PX] != '1')
		{
			img->strt_x -= cos(t_c3d.crnr) * 4;
			img->strt_y -= sin(t_c3d.crnr) * 4;
			t_c3d.crnr_s = t_c3d.crnr - M_PI_6;
			parse_map(img, sprts, data);
		}
	}
	if (LEFT)
	{
		t_c3d.crnr += (t_c3d.crnr - 0.2 < 0) ? M_PI * 2 - 0.2 : -0.2;
		t_c3d.crnr_s = t_c3d.crnr - M_PI_6;
		t_c3d.crnr_e = t_c3d.crnr + M_PI_6;
		parse_map(img, sprts, data);
	}
	if (RIGHT)
	{
		t_c3d.crnr += (t_c3d.crnr + 0.2 > M_PI * 2) ? -t_c3d.crnr + 0.2 : 0.2;
		t_c3d.crnr_s = t_c3d.crnr - M_PI_6;
		t_c3d.crnr_e = t_c3d.crnr + M_PI_6;
		parse_map(img, sprts, data);
	}
	printf("key == %#x\n", key);
	if (key == 0x35)
		exit(123);
	return 1;
}

void	txtr_init(s_data *data)
{
	t_txtr.txtr_ea.img = mlx_xpm_file_to_image(data->mlx.mlx, t_c3d.ea_t, &t_txtr.txtr_ea.w_xpm, &t_txtr.txtr_ea.h_xpm);
	t_txtr.txtr_ea.addr = mlx_get_data_addr(t_txtr.txtr_ea.img, &t_txtr.txtr_ea.bpp, &t_txtr.txtr_ea.l_len, &t_txtr.txtr_ea.endian);

	t_txtr.txtr_no.img = mlx_xpm_file_to_image(data->mlx.mlx, t_c3d.no_t, &t_txtr.txtr_no.w_xpm, &t_txtr.txtr_no.h_xpm);
	t_txtr.txtr_no.addr = mlx_get_data_addr(t_txtr.txtr_no.img, &t_txtr.txtr_no.bpp, &t_txtr.txtr_no.l_len, &t_txtr.txtr_no.endian);

	t_txtr.txtr_so.img = mlx_xpm_file_to_image(data->mlx.mlx, t_c3d.so_t, &t_txtr.txtr_so.w_xpm, &t_txtr.txtr_so.h_xpm);
	t_txtr.txtr_so.addr = mlx_get_data_addr(t_txtr.txtr_so.img, &t_txtr.txtr_so.bpp, &t_txtr.txtr_so.l_len, &t_txtr.txtr_so.endian);

	t_txtr.txtr_we.img = mlx_xpm_file_to_image(data->mlx.mlx, t_c3d.we_t, &t_txtr.txtr_we.w_xpm, &t_txtr.txtr_we.h_xpm);
	t_txtr.txtr_we.addr = mlx_get_data_addr(t_txtr.txtr_we.img, &t_txtr.txtr_we.bpp, &t_txtr.txtr_we.l_len, &t_txtr.txtr_we.endian);

	t_sprt.img = mlx_xpm_file_to_image(data->mlx.mlx, t_c3d.sp_t, &t_sprt.wdth, &t_sprt.hght);
	t_sprt.addr = mlx_get_data_addr(t_sprt.img, &t_sprt.bpp, &t_sprt.l_len, &t_sprt.endian);

}

int main(int argc, char **argv)
{
	t_img img;
	t_coors *sprts;
	s_data data;

	(argc != 2) ? exit(45) : printf("фисё окк\n");
	prs_cub3d(argv[1], &sprts);
	data.mlx.mlx = mlx_init();
	txtr_init(&data);
	data.mlx.wnd = mlx_new_window(data.mlx.mlx, t_c3d.x_r, t_c3d.y_r, "cub3d");
	img.img = mlx_new_image(data.mlx.mlx, t_c3d.x_r, t_c3d.y_r);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.l_len, &img.endian);
	parse_map(&img, sprts, &data);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.wnd, img.img, 0, 0);
	mlx_hook(data.mlx.wnd, 2, 0L, start, &img);
    mlx_loop(data.mlx.mlx);
	return (0);
}
