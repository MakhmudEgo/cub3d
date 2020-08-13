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
static void map_fill(char *s, int current, int last, char **ss)
{
	int n;
	int s_len;
	int s_bf;
	int s_af;

	n = 0;
	s_len = ft_strlen(s);
    s_bf = current != 0 ? ft_strlen(ss[current - 1]) : 0;
    s_af = current != last ? ft_strlen(ss[current + 1]) : 0;
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

// Мой Роджер ------------------------------------------------------------------------
	/*while (s[n])
	{
		if ((current == 0 && s[n] != '1' && s[n] != ' ')
		|| (current == last && s[n] != '1'  && s[n] != ' ')
		|| (s[0] != '1' && s[0] != ' ')
		|| (s[s_len - 1] != '1' && s_len - 1 == n)
		|| (s[n - 1] == ' ' && s[n] == '0'))
		{
			s[n] = '1';
			printf("Карта не валидная, но мой ИИ-Роджер исправил это.\n"
          "Ошибка в %d строке\n"
          "Символ %d\n"
          "Давайте скажем Роджеру – Спасибо!\n",
          current + 1, n + 1);
		}
		n++;
	}*/
	// Джесика
	while (s[n])
    {
	    if (s[n] == '0' &&
            (current == 0 || current == last ||
            (s_bf <= n && current != 0) || (s_af <= n && current != last)
            || (n != 0 && s[n - 1] == ' ') || s[n + 1] == ' '
            || s[n + 1] == '\0' || n == 0
            || (current < last && ss[current + 1][n] == ' '))
	    )
        {
	        /*printf("Джесика Молодец! нашла ошибку в карте и исправила\n"
                "в строке %d\n"
                "Символ %d\n", current, n);*/
            s[n] = '1';
        }
	    n++;
    }
	printf("%s\n", s);
}

// Мой Роджер ------------------------------------------------------------------------

void create_map(t_list *t_map)
{
	int map_size;
	int i;

	map_size = ft_lstsize(t_map);
	t_cub3d.map = malloc(sizeof(char*) * map_size); // char map;
	t_cub3d.map_int = malloc(sizeof(int*) * map_size); //int map;
	t_cub3d.map[map_size - 1] = 0x0; // char map
	t_cub3d.map_int[map_size - 1] = 0x0; //int map;
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
//			map_fill(t_map->content, i, map_size - 2);
//			printf("%s\n", (t_cub3d.map)[map_size]);
			i++;
		} else
			free(t_map->next);
		t_map = t_map->next;
	}
	i = 0;
	while ((t_cub3d.map)[i])
    {
        map_fill((t_cub3d.map)[i], i, map_size - 2, t_cub3d.map);
        i++;
    }

}
