/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 03:11:49 by mizola            #+#    #+#             */
/*   Updated: 2020/08/29 21:55:42 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isprint(int c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}
