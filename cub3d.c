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

void	*get_xpm_img(t_data *data, t_img *img, char *p)
{
	void *ptr;

	ptr = mlx_xpm_file_to_image(data->mlx.mlx, p, &img->w_xpm, &img->h_xpm);
	free(p);
	return (ptr);
}

void	txtr_init(t_data *data)
{
	data->txtr_ea.img = get_xpm_img(data, &data->txtr_ea, data->ea_t);
	data->txtr_no.img = get_xpm_img(data, &data->txtr_no, data->no_t);
	data->txtr_so.img = get_xpm_img(data, &data->txtr_so, data->so_t);
	data->txtr_we.img = get_xpm_img(data, &data->txtr_we, data->we_t);
	data->txtr_sp.img = get_xpm_img(data, &data->txtr_sp, data->sp_t);
	if (data->txtr_ea.img && data->txtr_no.img &&
	data->txtr_so.img && data->txtr_we.img && data->txtr_sp.img)
	{
		data->txtr_ea.addr = mlx_get_data_addr(data->txtr_ea.img,
		&data->txtr_ea.bpp, &data->txtr_ea.l_len, &data->txtr_ea.endian);
		data->txtr_no.addr = mlx_get_data_addr(data->txtr_no.img,
		&data->txtr_no.bpp, &data->txtr_no.l_len, &data->txtr_no.endian);
		data->txtr_so.addr = mlx_get_data_addr(data->txtr_so.img,
		&data->txtr_so.bpp, &data->txtr_so.l_len, &data->txtr_so.endian);
		data->txtr_we.addr = mlx_get_data_addr(data->txtr_we.img,
		&data->txtr_we.bpp, &data->txtr_we.l_len, &data->txtr_we.endian);
		data->txtr_sp.addr = mlx_get_data_addr(data->txtr_sp.img,
		&data->txtr_sp.bpp, &data->txtr_sp.l_len, &data->txtr_sp.endian);
	}
	else
		exit_notify("texture file ko\n", 45);
}

void	check_arg_exp(char **s, int argc, t_data *data)
{
	if (argc == 3)
		(!ft_strncmp(s[1], s[2], 6) || ft_strlen(s[2]) != 6)
		? exit_notify("No valid argv\n", 77) : 0;
	if ((ft_strlen(s[1]) < 5)
	|| ft_strncmp(&s[1][ft_strlen(s[1]) - 4], ".cub", 4))
		exit_notify("No valid exp .cub\n", 55);
	data->scrn = argc == 3 ? 1 : 0;
}

int		close_wnd(int code)
{
	if (!code)
		exit(0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_data data;

	(argc < 2 || argc > 3) ? exit_notify("No valid argc\n", 55)
	: check_arg_exp(argv, argc, &data);
	data.mlx.mlx = mlx_init();
	prs_cub3d(argv[1], &data) ? exit_notify("No valid arg\n", 55) : 0;
	txtr_init(&data);
	data.mlx.wnd = mlx_new_window(data.mlx.mlx, data.x_r,
	data.y_r, "cub3d");
	!(data.img.img = mlx_new_image(data.mlx.mlx, data.x_r, data.y_r))
	? exit_notify("No Image\n", 11) : 0;
	data.img.addr = mlx_get_data_addr(data.img.img,
	&data.img.bpp, &data.img.l_len, &data.img.endian);
	parse_map(&data);
	mlx_put_image_to_window(data.mlx.mlx, data.mlx.wnd, data.img.img, 0, 0);
	mlx_hook(data.mlx.wnd, 2, 1L, move, &data);
	mlx_hook(data.mlx.wnd, 17, 0L, close_wnd, 0);
	mlx_loop(data.mlx.mlx);
	return (0);
}
