/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharw_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 05:58:31 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/25 10:23:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_printf.h"

static size_t		count_bits(unsigned int c)
{
	int	count;

	count = 0;
	while (c)
	{
		c >>= 1;
		++count;
	}
	return (count);
}

static size_t		count_bytes(size_t bits)
{
	int	bytes;

	if (bits < 8)
		return (1);
	bytes = 2;
	while ((int)bits - (8 - ((int)bytes + 1)) - ((int)(bytes - 1) * 6) > 0)
		++bytes;
	return (bytes);
}

static unsigned int	get_n_bits(unsigned int c, size_t n, char *byte)
{
	*byte = 0;
	while (n)
	{
		*byte = (*byte) << 1;
		*byte = *byte + (char)((c & 0x80000000) >> 31);
		c <<= 1;
		--n;
	}
	return (c);
}

static wchar_t		write_first_byte(unsigned int c, size_t bits,
		size_t byte_count, t_printf_buffer *buffer)
{
	char	tmp_byte;

	while (c && !(c & 0x80000000))
		c <<= 1;
	c = get_n_bits(c, bits - (byte_count - 1) * 6, &tmp_byte);
	if (byte_count == 2)
		tmp_byte |= 0xc0;
	else if (byte_count == 3)
		tmp_byte |= 0xe0;
	else
		tmp_byte |= 0xf0;
	add_to_buffer(buffer, tmp_byte);
	return (c);
}

int					ft_putcharw_buffer(t_printf_buffer *buffer, wchar_t c)
{
	size_t	byte_count;
	size_t	bits;
	char	tmp_byte;

	bits = count_bits((unsigned int)c);
	if ((byte_count = count_bytes(bits)) > 4)
		return (-1);
	tmp_byte = (char)c;
	if (byte_count == 1)
		return (add_to_buffer(buffer, tmp_byte));
	else
	{
		c = write_first_byte(c, bits, byte_count, buffer);
		while (--byte_count)
		{
			c = get_n_bits(c, 6, &tmp_byte);
			tmp_byte |= 0x80;
			add_to_buffer(buffer, tmp_byte);
		}
		return (0);
	}
}
