/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_map2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 10:59:17 by mizola            #+#    #+#             */
/*   Updated: 2020/08/20 10:59:20 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_map(int x, int y, int clr, int size_px, t_img *img)
{
    int end_x;
    int strt_x;
    int end_y;
    int strt_y;

    strt_y = y * size_px;
    strt_x = x * size_px;
    x = strt_x;
    end_x = strt_x + size_px;
    end_y = strt_y + size_px;
    while (strt_x <= end_x)
    {
        my_mlx_pixel_put(img, strt_x, strt_y, clr);
        if (strt_x == end_x && strt_y < end_y)
        {
            strt_y++;
            strt_x = x;
        }
        else
            strt_x++;
    }
}

void move_player()
{

}

void    parse_map(t_img *img)
{
    int y;
    int x;
    int sz_px;

    y = 0;
    x = 0;
    sz_px = 25;
    while ((t_cub3d.map)[y])
    {
        while ((t_cub3d.map)[y][x])
        {
            if ((t_cub3d.map)[y][x] == '1')
                put_map(x, y, 0xff0000, sz_px, img);
            else if ((t_cub3d.map)[y][x] == '0')
                put_map(x, y, 0xffffff, sz_px, img);
            else if ((t_cub3d.map)[y][x] == '2')
                put_map(x, y, 0x0000ff, sz_px, img);
            else if ((t_cub3d.map)[y][x] == ' ')
                put_map(x, y, 0x0, sz_px, img);
            else
            {
                put_map(x, y, 0xffffff, sz_px, img);
                img->tmp_x = x;
                img->tmp_y = y;
            }
            x++;
        }
        x = 0;
        y++;
    }
    double dd = -0.3;
    float cc = 0;
    while (dd <= 0.7)
    {
        while (1)
        {
            short xx = img->tmp_x * sz_px + (sz_px / 2) + cc * cos(dd);
            short yy = img->tmp_y * sz_px + (sz_px / 2) + cc * sin(dd);
            cc += 1;
            my_mlx_pixel_put(img, xx, yy, 0xf000f0);
            if ((t_cub3d.map)[yy/25][xx/25] == '1')
                break;
        }
        cc = 0;
        dd += 0.01;
    }
    mlx_put_image_to_window(t_mlx.mlx, t_mlx.wnd, img->img, 0, 0);
}
