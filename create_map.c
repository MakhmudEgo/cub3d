/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 16:08:31 by mizola            #+#    #+#             */
/*   Updated: 2020/08/11 20:51:23 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map(t_data *data, int n, int current, int last)
{
	int		s_bf;
	int		s_af;
	char	*s;

	s_bf = current != 0 ? (int)ft_strlen(data->map[current - 1]) : 0;
	s_af = current != last ? (int)ft_strlen(data->map[current + 1]) : 0;
	s = data->map[current];
	return (((s[n] == '0' || s[n] == 'N') &&
	(current == 0 || current == last
	|| s_bf <= n || s_af <= n
	|| (n != 0 && s[n - 1] == ' ') || s[n + 1] == ' '
	|| s[n + 1] == '\0' || n == 0
	|| (current < last && data->map[current + 1][n] == ' ')
	|| (s_bf >= n && data->map[current - 1][n] == ' ')))
	|| !ft_strchr("12 0NWES", s[n])
	|| (current != last && data->map[current + 1][0] == '\0')
	|| data->plyr > 1);
}

void		get_orien(t_data *data, char c)
{
	if (c == E)
	{
		data->crnr = CRNR;
		data->crnr_s = M_PI * 2 - M_PI_6;
	}
	if (c == W)
	{
		data->crnr = M_PI;
		data->crnr_s = M_PI - M_PI_6;
	}
	if (c == N)
	{
		data->crnr = 3 * M_PI / 2;
		data->crnr_s = 3* M_PI / 2 - M_PI_6;
	}
	if (c == S)
	{
		data->crnr = M_PI / 2;
		data->crnr_s = M_PI / 2 - M_PI_6;
	}
}

static void	map_fill(char *s, int current, int last, t_data *data)
{
	int		n;

	n = 0;
	while (s[n])
	{
		if (ft_strchr("NWES", s[n]))
		{
			data->plyr++;
			data->strt_x = n * SZ_PX + (SZ_PX / 2);
			data->strt_y = current * SZ_PX + (SZ_PX / 2);
			get_orien(data, s[n]);
		}
		if (is_valid_map(data, n, current, last))
			exit_notify("No valid map\n", 66);
		if (s[n] == '2')
			sp_lstadd_back(&data->sprts, sp_lstnew(n * SZ_PX + (SZ_PX / 2),
			current * SZ_PX + (SZ_PX / 2), 0));
		n++;
	}
}

void		create_map(t_list *t_map, t_data *data)
{
	int map_size;
	int i;

	map_size = ft_lstsize(t_map);
	data->map = malloc(sizeof(char *) * map_size + 1);
	data->map[map_size] = 0x0;
	i = 0;
	while (t_map)
	{
		if (t_map->content)
		{
			(data->map)[i] = t_map->content;
			i++;
		}
		else
			free(t_map->next);
		t_map = t_map->next;
	}
	i = 0;
	while ((data->map)[i])
	{
		map_fill((data->map)[i], i, map_size - 1, data);
		i++;
	}
}
