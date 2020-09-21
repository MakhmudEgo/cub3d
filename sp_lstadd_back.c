/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 18:54:02 by mizola            #+#    #+#             */
/*   Updated: 2020/09/05 18:54:11 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sp_lstadd_back(t_coors **sprts, t_coors *new)
{
	t_coors *tmp;

	tmp = *sprts;
	if (!tmp && sprts)
		*sprts = new;
	else if (sprts && new)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}
