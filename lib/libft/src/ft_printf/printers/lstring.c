/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:31:30 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/15 11:31:27 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

#include "libft.h"
#include "ft_printf.h"

static size_t	get_padding_size(t_conv *c, const wchar_t *ws, size_t len)
{
	size_t			precision;
	size_t			wchar_size;
	unsigned int	i;

	i = 0;
	precision = len;
	while (ws[i] && precision >= (wchar_size = ft_char_size_utf8(ws[i])))
	{
		precision -= wchar_size;
		++i;
	}
	if (c->field_width >= len - precision)
		return (c->field_width - len + (c->precision_set ? precision : 0));
	return (0);
}

static void		print_space(t_conv *conv, size_t len, t_printf_buffer *buffer)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		if (conv->zero_padded && !conv->left_padded)
			add_to_buffer(buffer, '0');
		else
			add_to_buffer(buffer, ' ');
		++i;
	}
}

static int		print_wstring(wchar_t *ws, size_t len, t_printf_buffer *buffer)
{
	unsigned int	i;
	size_t			current_len;

	i = 0;
	current_len = ft_char_size_utf8(ws[i]);
	while (ws[i] && current_len <= len)
	{
		ft_putcharw_buffer(buffer, ws[i]);
		++i;
		current_len += ft_char_size_utf8(ws[i]);
	}
	return (0);
}

int				printer_lstring(void *conv, va_list *vl,
		t_printf_buffer *buffer)
{
	size_t	len;
	wchar_t	*arg;

	arg = va_arg((*vl), wchar_t *);
	if (((t_conv *)conv)->precision_set)
	{
		if (arg)
			len = ft_llmin(ft_strlenw(arg), ((t_conv *)conv)->precision);
		else
			len = ft_llmin(ft_strlenw(NULL_PRINTW)
					, ((t_conv *)conv)->precision);
	}
	else
		len = ft_strlenw(arg ? arg : NULL_PRINTW);
	if (!((t_conv *)conv)->left_padded)
		print_space(conv,
				get_padding_size(conv, arg ? arg : NULL_PRINTW, len), buffer);
	print_wstring(arg ? arg : NULL_PRINTW, len, buffer);
	if (((t_conv *)conv)->left_padded)
		print_space(conv,
				get_padding_size(conv, arg ? arg : NULL_PRINTW, len), buffer);
	return (0);
}
