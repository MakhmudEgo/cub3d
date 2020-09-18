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
static void map_fill(char *s, int current, int last, t_coors **sprts )
{
	int n;
	int s_bf;
	int s_af;
	char **ss = t_c3d.map;

	n = 0;
    s_bf = current != 0 ? ft_strlen(ss[current - 1]) : 0;
    s_af = current != last ? ft_strlen(ss[current + 1]) : 0;

    while (s[n])
    {
	    if (((s[n] == '0' || s[n] == 'N') &&
            (current == 0 || current == last
            || s_bf <= n || s_af <= n
            || (n != 0 && s[n - 1] == ' ') || s[n + 1] == ' '
            || s[n + 1] == '\0' || n == 0
            || (current < last && ss[current + 1][n] == ' ')
            || (s_bf >= n && ss[current - 1][n] == ' ')))
            || !ft_strchr("12 0NWES", s[n])
            || (current != last && ss[current + 1][0] == '\0')
            )
        {
	        /*printf("ИИ Джесика Молодец! нашла ошибку в карте и исправила\n"
                "в строке %d\n"
                "Символ %d\n", current, n);
            printf("x%d:y%d\n", current + 1, n + 1);*/
	        write(1, "запихни нормальную карту\n", 50);
	        exit(66);
            s[n] = '1';
        }
		if (s[n] == '2')
			sp_lstadd_back(sprts, sp_lstnew(n * SZ_PX + (SZ_PX / 2), current * SZ_PX + (SZ_PX / 2), 0));
	    n++;
    }
    printf("n = %d:|%s|\n", current, s);
}

t_coors *create_map(t_list *t_map)
{
	int map_size;
	int i;
	t_coors *sprts = 0x0;

	map_size = ft_lstsize(t_map);
	t_c3d.map = malloc(sizeof(char*) * map_size + 1);
	t_c3d.map[map_size] = 0x0;
	i = 0;

	while (t_map)
	{
		if (t_map->content)
		{
			(t_c3d.map)[i] = t_map->content;
			i++;
		} else
			free(t_map->next);
		t_map = t_map->next;
	}
	i = 0;
	while ((t_c3d.map)[i])
    {
        map_fill((t_c3d.map)[i], i, map_size - 1, &sprts);
        i++;
    }
	return (sprts);
}
