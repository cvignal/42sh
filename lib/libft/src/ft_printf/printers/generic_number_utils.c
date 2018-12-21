/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_number_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/17 09:37:28 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/26 11:53:24 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdint.h>

#include "libft.h"
#include "ft_printf.h"

static size_t		number_len_octal(t_conv *conv, long long nbr, size_t len)
{
	if (!nbr && !conv->precision_set)
		return (1);
	if (conv->precision <= (size_t)len)
		conv->precision = (size_t)len + 1;
	return (len);
}

size_t				print_flags(t_conv *conv, long long nbr,
		t_printf_buffer *buffer)
{
	if (!conv->sign && conv->space && (!conv->format->is_signed || nbr >= 0))
	{
		if (conv->format->is_signed)
		{
			add_to_buffer(buffer, ' ');
			return (1);
		}
	}
	return (0);
}

size_t				number_len(t_conv *conv, long long nbr)
{
	size_t		base_len;
	size_t		len;
	long long	nbr_save;

	nbr_save = nbr;
	base_len = ft_strlen(conv->format->base);
	len = 0;
	while (nbr)
	{
		++len;
		if (conv->format->is_signed)
			nbr /= (long long)base_len;
		else
			nbr /= (unsigned long long)base_len;
	}
	if ((conv->format->desc.desc == FORMAT_OCTAL_INT
				|| conv->format->desc.desc == FORMAT_OCTAL_INT2)
			&& conv->alternate)
		return (number_len_octal(conv, nbr_save, len));
	else if (!nbr_save && !conv->precision_set)
		return (1);
	if (!nbr_save && conv->precision_set)
		return (0);
	return (len ? len : 1);
}

unsigned long long	get_arg_signed(t_conv *conv, va_list *vl)
{
	if (conv->arg_size == sizeof(char))
		return ((char)va_arg(*vl, int));
	else if (conv->arg_size == sizeof(short))
		return ((short)va_arg(*vl, int));
	else if (conv->arg_size == sizeof(long))
		return (va_arg(*vl, long));
	else if (conv->arg_size == sizeof(long long))
		return (va_arg(*vl, long long));
	else if (conv->arg_size == sizeof(intmax_t))
		return (va_arg(*vl, intmax_t));
	else if (conv->arg_size == sizeof(size_t))
		return (va_arg(*vl, size_t));
	return (((int)va_arg(*vl, int)));
}

unsigned long long	get_arg_unsigned(t_conv *conv, va_list *vl)
{
	if (conv->arg_size == sizeof(char))
		return ((unsigned char)va_arg(*vl, int));
	else if (conv->arg_size == sizeof(short))
		return ((unsigned short)va_arg(*vl, int));
	else if (conv->arg_size == sizeof(long))
		return (va_arg(*vl, long));
	else if (conv->arg_size == sizeof(long long))
		return (va_arg(*vl, long long));
	else if (conv->arg_size == sizeof(intmax_t))
		return (va_arg(*vl, intmax_t));
	else if (conv->arg_size == sizeof(size_t))
		return (va_arg(*vl, size_t));
	return ((unsigned int)va_arg(*vl, int));
}
