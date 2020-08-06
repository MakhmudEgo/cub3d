/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 14:56:21 by mizola            #+#    #+#             */
/*   Updated: 2020/08/06 16:38:16 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_CUB3D_H
# define CUB3D_CUB3D_H

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include "minilibx/mlx.h"
# include <fcntl.h>

struct		t_parsecub3dfile
{
	int		**map;
	int		x_r;
	int		y_r;
	char	*no_t;
	char	*so_t;
	char	*we_t;
	char	*ea_t;
	char	*sp_t;
	char	*st_t;
	char	*ft_t;
	int		f_t;
	int		c_t;
}			t_cub3d;

void		prs_cub3d(char *argv);

#endif
