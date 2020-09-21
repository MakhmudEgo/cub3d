/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 18:47:06 by mizola            #+#    #+#             */
/*   Updated: 2020/09/05 18:47:30 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_coors	*sp_lstnew(double x, double y, double l_len)
{
	t_coors *new_el;

	new_el = malloc(sizeof(t_coors));
	if (new_el == NULL)
		return (NULL);
	new_el->x = x;
	new_el->y = y;
	new_el->l_len = l_len;
	new_el->next = NULL;
	return (new_el);
}
