/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_decimal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 14:40:38 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/21 18:11:22 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static unsigned long long	get_arg(t_conv *conv, va_list *vl)
{
	if (conv->format->is_signed)
		return (get_arg_signed(conv, vl));
	else
		return (get_arg_unsigned(conv, vl));
}

static size_t				print_precision(t_conv *conv, long long len,
		long long nbr, t_printf_buffer *buffer)
{
	int	i;

	i = 0;
	if ((conv->format->is_signed && nbr < 0) || conv->sign)
		--len;
	while (((int)conv->precision) - ((int)len) - i > 0)
	{
		add_to_buffer(buffer, '0');
		++i;
	}
	return (i);
}

size_t						print_prepend(t_conv *conv, long long nbr,
		int after_padding, t_printf_buffer *buffer)
{
	if (conv->alternate && conv->format->prepend && nbr)
	{
		if (!after_padding && conv->zero_padded && !conv->precision_set)
			add_to_buffer_nstring(buffer, conv->format->prepend,
					ft_strlen(conv->format->prepend));
		else if (after_padding && (!conv->zero_padded || conv->precision_set))
			add_to_buffer_nstring(buffer, conv->format->prepend,
					ft_strlen(conv->format->prepend));
		return (ft_strlen(conv->format->prepend));
	}
	return (0);
}

size_t						print_sign(t_conv *conv, long long arg,
		int after_padding, t_printf_buffer *buffer)
{
	if ((conv->zero_padded && !conv->precision_set && ((!after_padding
						&& (conv->format->desc.type == TYPE_INT
							|| conv->format->desc.type == TYPE_INT2))
					|| (after_padding && (conv->format->desc.type != TYPE_INT
							&& conv->format->desc.type != TYPE_INT2))))
			|| ((!conv->zero_padded || conv->precision_set)
				&& after_padding))
	{
		if (arg < 0 && conv->format->is_signed)
		{
			add_to_buffer(buffer, '-');
			return (1);
		}
		else if (conv->sign && conv->format->is_signed && arg >= 0)
		{
			add_to_buffer(buffer, '+');
			return (1);
		}
	}
	return (0);
}

int							printer_generic_number(void *c, va_list *vl,
		t_printf_buffer *buffer)
{
	unsigned long long	arg;
	long long			len;
	long long			max_len;

	arg = get_arg(c, vl);
	len = number_len(c, (long long)arg);
	max_len = MAX(((t_conv *)c)->precision, (unsigned long long)len);
	if ((((t_conv *)c)->format->is_signed && (long long)arg < 0)
			|| ((t_conv *)c)->sign)
	{
		++max_len;
		++len;
	}
	max_len += print_flags(c, arg, buffer);
	print_padding_left(c, max_len, arg, buffer);
	print_precision(c, len, arg, buffer);
	if ((((t_conv *)c)->precision_set && arg) || !((t_conv *)c)->precision_set)
		ft_putullnbr_base_buffer((((t_conv *)c)->format->is_signed) ?
				ABS((long long)arg) : (long long)arg,
				((t_conv *)c)->format->base, buffer);
	return (print_padding_right(c, max_len, arg, buffer));
}
