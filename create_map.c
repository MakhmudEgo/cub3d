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

static void map_fill(char *s, int current, int last, t_data *data)
{
	int		n;
	int		s_bf;
	int		s_af;

	n = 0;
    s_bf = current != 0 ? ft_strlen(data->map[current - 1]) : 0;
    s_af = current != last ? ft_strlen(data->map[current + 1]) : 0;
	data->max_width_map = s_bf > data->max_width_map ? s_bf : data->max_width_map;
	data->max_width_map = s_af > data->max_width_map ? s_bf : data->max_width_map;
    while (s[n])
    {
		data->plyr += (ft_strchr("NWES", s[n]) ? 1 : 0);
		if (((s[n] == '0' || s[n] == 'N') &&
            (current == 0 || current == last
            || s_bf <= n || s_af <= n
            || (n != 0 && s[n - 1] == ' ') || s[n + 1] == ' '
            || s[n + 1] == '\0' || n == 0
            || (current < last && data->map[current + 1][n] == ' ')
            || (s_bf >= n && data->map[current - 1][n] == ' ')))
            || !ft_strchr("12 0NWES", s[n])
            || (current != last && data->map[current + 1][0] == '\0')
            || data->plyr > 1
            )
			exit_notify("No valid map\n", 66);
		if (s[n] == '2')
			sp_lstadd_back(&data->sprts, sp_lstnew(n * SZ_PX + (SZ_PX / 2), current * SZ_PX + (SZ_PX / 2), 0));
	    n++;
    }
}

void create_map(t_list *t_map, t_data *data) {
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
