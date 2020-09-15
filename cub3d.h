/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:56:21 by mizola            #+#    #+#             */
/*   Updated: 2020/08/23 13:24:26 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB3D_H

# define CUB3D_CUB3D_H
# define N 'N'
# define S 'S'
# define E 'E'
# define W 'W'
# define GAME 1
# define SZ_PX 64
# define UP key == 0x7e || key == 0xd
# define DOWN key == 0x7d || key == 0x1
# define LEFT key == 0x7b || key == 0
# define RIGHT key == 0x7c || key == 0x2
# define L_RT key == 0xc || key == 0x56
# define R_RT key == 0xe || key == 0x58
# define CRNR 0.0
# define M_PI_6 (M_PI/6)

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
	double 	plyr_x;
	double 	plyr_y;
	double crnr;
	double crnr_s;
	double crnr_e;
	double	cf_rcs;
}			t_c3d;

typedef struct  s_img
{
	void *img;
	char *addr;
	int bpp;
	int l_len;
	int endian;
	int w_xpm;
	int h_xpm;
	double strt_x;
	double strt_y;
} t_img;

typedef struct s_coordisntsprites
{
	double x;
	double y;
	double l_len;
	struct s_coordisntsprites *next;
} t_coors;

struct s_sprite
{
	void *img;
	char *addr;
	int bpp;
	int l_len;
	int endian;
	int wdth;
	int hght;
} t_sprt;



struct s_txtr
{
	t_img txtr_no;
	t_img txtr_we;
	t_img txtr_so;
	t_img txtr_ea;
	t_img txtr_sp;
} t_txtr;

typedef struct s_mlx
{
	void *mlx;
	void *wnd;
} t_mlx;

typedef struct s_data {
	t_mlx mlx;
	t_img img;
	t_coors *sprts;
} t_data;

void		prs_cub3d(char *argv, t_coors **sprts);
t_coors		*create_map(t_list *t_map);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		parse_map(t_data *data);
void		sp_lstadd_back(t_coors **sprts, t_coors *new);
t_coors		*sp_lstnew(double x, double y, double l_len);
int	sp_lstsize(t_coors *lst);

#endif
