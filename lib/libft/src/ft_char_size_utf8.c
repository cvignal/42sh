/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_size_utf8.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 10:17:30 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/25 11:28:55 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_char_size_utf8(unsigned int c)
{
	size_t		size;
	size_t		bits;

	bits = 0;
	while (c)
	{
		++bits;
		c >>= 1;
	}
	if (bits < 8)
		return (1);
	size = 2;
	while ((int)bits - (8 - ((int)size + 1)) - (((int)size - 1) * 6) > 0)
		++size;
	return (size);
}
