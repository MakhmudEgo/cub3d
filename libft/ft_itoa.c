/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mizola <mizola@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 14:44:26 by mizola            #+#    #+#             */
/*   Updated: 2020/05/11 23:13:15 by mizola           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	num_len(int n)
{
	int				i;
	long long int	tmp;

	i = 0;
	tmp = n;
	if (n < 0)
	{
		i++;
		tmp *= (-1);
	}
	while (tmp >= 10)
	{
		tmp /= 10;
		i++;
	}
	return (i + 2);
}

static void	push_char(char *s, int n)
{
	long long int	res;
	int				signed_n;

	res = n;
	signed_n = 0;
	if (n < 0)
	{
		res *= (-1);
		signed_n = 1;
	}
	while (res)
	{
		*s = res % 10 + '0';
		res /= 10;
		s++;
	}
	if (signed_n)
	{
		*s = '-';
		s++;
	}
	*s = '\0';
}

static void	str_reverse(char *str, int i)
{
	char	tmp;
	int		n;
	int		j;

	n = 0;
	j = i - 2;
	while (n < (i - 1) / 2)
	{
		tmp = str[j];
		str[j] = str[n];
		str[n] = tmp;
		n++;
		j--;
	}
}

char		*ft_itoa(int n)
{
	char	*res;
	int		i;

	i = num_len(n);
	res = malloc(sizeof(char) * i);
	if (res == NULL)
		return (NULL);
	if (n == 0)
	{
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	push_char(res, n);
	str_reverse(res, i);
	return (res);
}
