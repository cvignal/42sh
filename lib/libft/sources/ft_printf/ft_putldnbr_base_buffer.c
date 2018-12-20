/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putldnbr_base_buffer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 05:52:16 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/26 11:23:51 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static size_t		get_nbr_size_base(long double nb, unsigned long int base)
{
	size_t	size;

	size = 0;
	if (!(int)nb)
		return (1);
	while (nb >= 1.0)
	{
		nb /= base;
		++size;
	}
	return (size);
}

static void			final_carry(t_printf_buffer *buffer, size_t len)
{
	add_to_buffer(buffer, '0');
	ft_memmove(buffer->data + buffer->pos - len,
			buffer->data + buffer->pos - len - 1, len);
	buffer->data[buffer->pos - len - 1] = '1';
}

static void			carry_buffer(t_printf_buffer *buffer, size_t len)
{
	unsigned int	i;
	unsigned int	carry;

	i = 0;
	carry = 1;
	while (i < len && carry)
	{
		if (buffer->data[buffer->pos - i - 1] != '.')
		{
			buffer->data[buffer->pos - i - 1] += 1;
			if (buffer->data[buffer->pos - i - 1] > '9')
			{
				buffer->data[buffer->pos - i - 1] = '0';
				carry = 1;
			}
			else
				carry = 0;
		}
		++i;
	}
	if (carry)
		final_carry(buffer, len);
}

static long double	handle_sign(long double nb, t_printf_buffer *buffer)
{
	if (nb < 0)
	{
		add_to_buffer(buffer, '-');
		return (-nb);
	}
	return (nb);
}

size_t				ft_putldnbr_base_buffer(long double nb, const char *base,
		unsigned int precision, t_printf_buffer *buffer)
{
	size_t				size;
	size_t				base_len;
	unsigned int		i;

	base_len = ft_strlen(base);
	nb = handle_sign(nb, buffer);
	size = get_nbr_size_base(nb, base_len);
	nb /= ft_ldpow(base_len, size);
	if (nb != nb)
		add_to_buffer_nstring(buffer, NAN_PRINT, ft_strlen(NAN_PRINT));
	i = 0;
	while (i < size + precision)
	{
		nb *= 10;
		add_to_buffer(buffer, *(base + ((int)nb % base_len)));
		nb -= (int)nb;
		++i;
		if (i == size && precision)
			add_to_buffer(buffer, '.');
	}
	if (nb * base_len >= 5)
		carry_buffer(buffer, size + precision + 1);
	return (0);
}
