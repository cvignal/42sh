/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 10:00:37 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/21 18:11:44 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "ft_printf.h"
#include "libft.h"

static int			print_nan(t_conv *conv, t_printf_buffer *buffer,
		const char *nan)
{
	size_t		len;
	size_t		len_arg;

	len_arg = ft_strlen(nan);
	if (conv->field_width > len_arg)
		len = conv->field_width - len_arg;
	else
		len = 0;
	conv->zero_padded = 0;
	if (!conv->left_padded)
		print_padding_double(conv, len, buffer);
	add_to_buffer_nstring(buffer, nan, ft_strlen(NAN_PRINT));
	if (conv->left_padded)
		print_padding_double(conv, len, buffer);
	return (0);
}

static double long	get_arg(t_conv *conv, va_list *vl)
{
	if (conv->arg_size == sizeof(double))
		return ((long double)va_arg(*vl, double));
	else
		return (va_arg(*vl, long double));
}

int					printer_double(void *conv, va_list *vl,
		t_printf_buffer *buffer)
{
	long double	arg;
	int			len;

	arg = get_arg(conv, vl);
	if ((len = get_padding_length_double(conv, arg)) == -1)
	{
		if (((t_conv *)conv)->arg_size == sizeof(double))
			return (print_nan(conv, buffer, NAN_PRINT));
		else
			return (print_nan(conv, buffer, NAN_PRINTC));
	}
	print_flags_double_left(conv, arg, len, buffer);
	if (!((t_conv *)conv)->left_padded)
		print_padding_double(conv, len, buffer);
	print_flags_double_right(conv, arg, len, buffer);
	ft_putldnbr_base_buffer(arg, "0123456789",
			((t_conv *)conv)->precision_set ? ((t_conv *)conv)->precision : 6,
			buffer);
	if (((t_conv *)conv)->left_padded)
		print_padding_double(conv, len, buffer);
	return (0);
}
