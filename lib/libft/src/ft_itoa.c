/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 02:49:25 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/12 22:17:01 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>

static char	*alloc_buffer(int value, size_t *size)
{
	int		pow;
	char	*res;

	if (value == INT_MIN)
		++value;
	if (value < 0)
		value = -value;
	pow = 1;
	*size = 1;
	while (value / pow > 9)
	{
		pow *= 10;
		++(*size);
	}
	if (!*size)
		*size = 1;
	res = malloc(sizeof(*res) * (*size + 2));
	return (res);
}

char		*ft_itoa(int value)
{
	size_t	size;
	char	*res;
	int		sign;

	res = alloc_buffer(value, &size);
	if (!res)
		return (NULL);
	if (value < 0)
	{
		sign = -1;
		++size;
	}
	else
		sign = 1;
	res[size] = 0;
	while (size)
	{
		res[--size] = value % 10 * sign + '0';
		value /= 10;
	}
	if (sign == -1)
		*res = '-';
	return (res);
}
