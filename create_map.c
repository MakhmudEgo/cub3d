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
static void map_fill(char *s, int i)
{
	int n;

	n = 0;
	while (s && *s)
	{
		if (*s == ' ' || *s == '1')
			t_cub3d.map_int[i][n] = 1;
		else if (*s == '2')
			t_cub3d.map_int[i][n] = 2;
		else if (*s == '0')
			t_cub3d.map_int[i][n] = 0;
		else if (*s == 'N' && !t_cub3d.orien)
			t_cub3d.map_int[i][n] = N;
		else if (*s == 'S' && !t_cub3d.orien)
			t_cub3d.map_int[i][n] = S;
		else if (*s == 'E' && !t_cub3d.orien)
			t_cub3d.map_int[i][n] = E;
		else if (*s == 'W' && !t_cub3d.orien)
			t_cub3d.map_int[i][n] = W;
		if ((*s == 'W' || *s == 'E' || *s == 'S' || *s == 'N') && !t_cub3d.orien)
			t_cub3d.orien = t_cub3d.map_int[i][n];
		else if (*s == 'W' || *s == 'E' || *s == 'S' || *s == 'N')
			t_cub3d.map_int[i][n] = 0;
		n++;
		s++;
	}
}

void create_map(t_list *t_map)
{
	int map_size;

	map_size = ft_lstsize(t_map);
	t_cub3d.map = malloc(sizeof(char*) * map_size); // char map;
	t_cub3d.map_int = malloc(sizeof(int*) * map_size); //int map;
	t_cub3d.map[map_size - 1] = 0x0; // char map
	t_cub3d.map_int[map_size - 1] = 0x0; //int map;
	map_size = 0;

// int's map
   while (t_map)
	{
		if (t_map->content)
		{
			(t_cub3d.map_int)[map_size] = malloc(sizeof(int) * (ft_strlen(t_map->content) + 1));
			map_fill(t_map->content, map_size);
			(t_cub3d.map_int)[map_size][ft_strlen(t_map->content)] = 5;
			int n = 0;
			while ((t_cub3d.map_int)[map_size][n] != 5)
			{
				printf("%d", (t_cub3d.map_int)[map_size][n]);
				n++;
			}
			printf("%d\n", (t_cub3d.map_int)[map_size][n]);
			map_size++;
		}
		t_map = t_map->next;
	}

/*	while (t_map)
	{
		if (t_map->content)
		{
			(t_cub3d.map)[map_size] = t_map->content;
			printf("%s\n", (t_cub3d.map)[map_size]);
			map_size++;
		} else
			free(t_map->next);
		t_map = t_map->next;
	}*/
}
