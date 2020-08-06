/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 21:55:24 by mizola            #+#    #+#             */
/*   Updated: 2020/05/13 22:06:12 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *new_el;

	new_el = malloc(sizeof(t_list));
	if (new_el == NULL)
		return (NULL);
	new_el->content = content;
	new_el->next = NULL;
	return (new_el);
}
