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
static void map_fill(char *s, int current, int last)
{
	int n;
	int s_len;

	n = 0;
	s_len = ft_strlen(s);
	// for int's map
/*	while (s && *s)
	{
		if (*s == ' ' || *s == '1')
			t_cub3d.map_int[current][n] = 1;
		else if (*s == '2')
			t_cub3d.map_int[current][n] = 2;
		else if (*s == '0')
			t_cub3d.map_int[current][n] = 0;
		else if (*s == 'N' && !t_cub3d.orien)
			t_cub3d.map_int[current][n] = N;
		else if (*s == 'S' && !t_cub3d.orien)
			t_cub3d.map_int[current][n] = S;
		else if (*s == 'E' && !t_cub3d.orien)
			t_cub3d.map_int[current][n] = E;
		else if (*s == 'W' && !t_cub3d.orien)
			t_cub3d.map_int[current][n] = W;
		if ((*s == 'W' || *s == 'E' || *s == 'S' || *s == 'N') && !t_cub3d.orien)
			t_cub3d.orien = t_cub3d.map_int[current][n];
		else if (*s == 'W' || *s == 'E' || *s == 'S' || *s == 'N')
			t_cub3d.map_int[current][n] = 0;
		n++;
		s++;
	}*/

	while (s[n])
	{
		if ((current == 0 && s[n] != '1')
		|| (current == last && s[n] != '1')
		|| (s[0] != '1' && s[0] != ' ') || s[s_len - 1] != '1'
		|| (s[n - 1] == ' ' && s[n] == '0'))
		{
			s[n] = '1';
			printf("Карта не валидная, мой ИИ исправил это.\nОшибка в %d\nСимволь %d\n", current + 1, n + 1);
		}
//		if (s[0] != '1' || s[s_len - 1] != '1')
//			exit(17);
		n++;
	}
	printf("%s\n", s);
}

void create_map(t_list *t_map)
{
	int map_size;
	int i;

	map_size = ft_lstsize(t_map);
	t_cub3d.map = malloc(sizeof(char*) * map_size); // char map;
	t_cub3d.map_int = malloc(sizeof(int*) * map_size); //int map;
	t_cub3d.map[map_size - 1] = 0x0; // char map
	t_cub3d.map_int[map_size - 1] = 0x0; //int map;
//	map_size = 0;
	i = 0;

// int's map
/*   while (t_map)
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
	}*/

	while (t_map)
	{
		if (t_map->content)
		{
			(t_cub3d.map)[i] = t_map->content;
			map_fill(t_map->content, i, map_size - 2);
//			printf("%s\n", (t_cub3d.map)[map_size]);
			i++;
		} else
			free(t_map->next);
		t_map = t_map->next;
	}
}
