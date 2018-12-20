/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 10:49:18 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/06 17:56:07 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "libft.h"

static int		get_pow(int n)
{
	int	pow;

	pow = 1;
	while (n / 10)
	{
		n /= 10;
		pow *= 10;
	}
	return (pow);
}

static size_t	get_nbr_size(int n)
{
	size_t	size;

	size = 0;
	while (n)
	{
		++size;
		n /= 10;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	char			*res;
	int				pow;
	unsigned int	i;
	unsigned int	sign;

	res = malloc(sizeof(*res) * (get_nbr_size(n) + 1));
	if (!res)
		return (NULL);
	pow = get_pow(n);
	i = 0;
	if (n < 0)
	{
		res[i++] = '-';
		sign = -1;
	}
	else
		sign = 1;
	while (pow)
	{
		res[i++] = (n / pow) * sign + '0';
		n %= pow;
		pow /= 10;
	}
	res[i] = 0;
	return (res);
}
