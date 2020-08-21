/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:56:21 by mizola            #+#    #+#             */
/*   Updated: 2020/08/21 10:52:55 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB3D_H

# define CUB3D_CUB3D_H
# define N 'N'
# define S 'S'
# define E 'E'
# define W 'W'
# define GAME 1

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "minilibx/mlx.h"
# include <fcntl.h>

struct		s_parsecub3dfile
{
	char	**map;
	int		**map_int;
	int		x_r;
	int		y_r;
	char	*no_t;
	char	*so_t;
	char	*we_t;
	char	*ea_t;
	char	*sp_t;
	int		f_t;
	int		c_t;
	char	orien;
	short 	plyr_x;
	short 	plyr_y;
	double	crnr;
	short	cf_rcs;
}			t_c3d;

typedef struct  s_img
{
	void *img;
	char *addr;
	int bpp;
	int l_len;
	int endian;
	int strt_x;
	int strt_y;
} t_img;

struct ha
{
	void *mlx;
	void *wnd;
} t_mlx;

void		prs_cub3d(char *argv);
void		create_map(t_list *t_map);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		parse_map(t_img *img);

#endif
