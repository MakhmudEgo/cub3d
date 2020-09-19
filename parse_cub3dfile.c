/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub3dfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:30:40 by mizola            #+#    #+#             */
/*   Updated: 2020/08/23 12:47:55 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void t_data_init(t_data *data)
{
	data->map = 0x0;
	data->x_r = 0x0;
	data->y_r = 0x0;
	data->no_t = 0x0;
	data->so_t = 0x0;
	data->we_t = 0x0;
	data->ea_t = 0x0;
	data->sp_t = 0x0;
	data->f_t = 0x0;
	data->c_t = 0x0;
	data->orien = 0x0;
	data->plyr_x = 0x0;
	data->plyr_y = 0x0;
	data->cf_rcs = 1;
	data->crnr = CRNR;
	data->crnr_s = M_PI * 2 - M_PI_6;
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

void	prs_cub3d_fc(char *s, char c, t_data *data)
{
	int r;
	int g;
	int b;
	char *tmp = s;

	r = ft_atoi(s);
	while (*(s - 1) != ',' && *s != '\0')
		s++;
	g = ft_atoi(s);
	while (*s != ',' && *s != '\0')
		s++;
	b = ft_atoi(s + 1);
	if (c == 'F')
		data->f_t = create_trgb(0, r, g, b);
	else
		data->c_t = create_trgb(0, r, g, b);
	free(tmp);
}
static void is_valid_data(const char *s)
{
	int i;
	int n;

	i = -1;
	while (s && s[++i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != ' ')
			exit(22);
	}
	i = -1;
	n = 0;
	while (s && s[i] && s[++i])
	{
		if (s[i] && s[i] != ' ')
		{
			while (s[i] && s[i] != ' ')
				i++;
			n++;
		}
	}
	(n != 2 ? exit(22) : write(1, "screen size ok22\n", 17));
}
void prs_cub3d_ass(char *s, t_list **t_map, t_data *data)
{
	if (*s == 'R')
	{
		is_valid_data(++s);
		data->x_r = ft_atoi(s);
		while (s && *s == ' ' && *s != '\0')
			s++;
		while (s && *s != ' ' && *s != '\0')
			s++;
		data->y_r = ft_atoi(s);
	}
	else if (*s == 'N' && *(s + 1) == 'O')
		data->no_t = ft_strtrim(s + 3, " ");
	else if (*s == 'S' && *(s + 1) == 'O')
		data->so_t = ft_strtrim(s + 3, " ");
	else if (*s == 'W' && *(s + 1) == 'E')
		data->we_t = ft_strtrim(s + 3, " ");
	else if (*s == 'E' && *(s + 1) == 'A')
		data->ea_t = ft_strtrim(s + 3, " ");
	else if (*s == 'S' && *(s + 1) != 'O')
		data->sp_t = ft_strtrim(s + 2, " ");
	else if(*s == 'F' || *s == 'C')
		prs_cub3d_fc(ft_strtrim(s + 2, " "), *s, data);
	else
		ft_lstadd_back(t_map, ft_lstnew(s));
}

int prs_cub3d(char *argv, t_data *data)
{
	char *line;
	int fd;
	t_list *t_map;

	t_map = 0x0;
	t_data_init(data);
	fd = open(argv, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		if (*line != '\0' || (*line == '\0' && t_map))
			prs_cub3d_ass(line, &t_map, data);
	}
	if (*line != '\0')
		prs_cub3d_ass(line, &t_map, data);
	create_map(t_map, data);
	return 0;
}