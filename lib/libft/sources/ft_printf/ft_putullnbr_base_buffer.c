/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putullnbr_base_buffer.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 05:50:37 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/24 06:19:18 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static size_t	get_nbr_size_base(unsigned long long nb,
		unsigned long long base)
{
	size_t	size;

	size = 0;
	if (!nb)
		return (1);
	while (nb)
	{
		nb /= base;
		++size;
	}
	return (size);
}

size_t			ft_putullnbr_base_buffer(unsigned long long nb,
		const char *base, t_printf_buffer *buffer)
{
	size_t				size;
	size_t				base_len;
	unsigned long long	pow;

	base_len = ft_strlen(base);
	size = get_nbr_size_base(nb, base_len);
	while (size--)
	{
		pow = ft_ullpow(base_len, size);
		add_to_buffer(buffer, *(base + nb / pow));
		nb %= pow;
	}
	return (0);
}
