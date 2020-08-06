/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 02:45:27 by mizola            #+#    #+#             */
/*   Updated: 2020/05/14 03:08:00 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *tmp;

	tmp = *lst;
	if (!tmp && lst)
		*lst = new;
	else if (lst && new)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->next = NULL;
	}
}
