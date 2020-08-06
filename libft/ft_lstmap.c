/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 09:06:34 by mizola            #+#    #+#             */
/*   Updated: 2020/05/14 09:06:35 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *res;
	t_list *new_lst;

	res = NULL;
	if (f)
	{
		while (lst)
		{
			new_lst = ft_lstnew((*f)(lst->content));
			if (!new_lst)
			{
				ft_lstclear(&res, del);
				return (res);
			}
			ft_lstadd_back(&res, new_lst);
			lst = lst->next;
		}
	}
	return (res);
}
