/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 15:39:53 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/24 22:15:48 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

#include "ft_printf.h"
#include "libft.h"

static size_t	get_arg_len(unsigned long long arg)
{
	size_t	i;

	if (!arg)
		return (1);
	i = 0;
	while (arg)
	{
		arg /= 16;
		++i;
	}
	return (i);
}

static int		print_precision(t_conv *conv, size_t arg_len,
		t_printf_buffer *buffer)
{
	int			i;

	i = 0;
	if (conv->precision_set)
	{
		while ((int)conv->precision - (int)arg_len - i > 0)
		{
			add_to_buffer(buffer, '0');
			++i;
		}
	}
	return (0);
}

static int		print_padding(t_conv *conv, size_t arg_len,
		t_printf_buffer *buffer)
{
	int		i;

	i = 0;
	while ((int)conv->field_width - (int)arg_len - i > 0)
	{
		if (conv->zero_padded)
			add_to_buffer(buffer, '0');
		else
			add_to_buffer(buffer, ' ');
		++i;
	}
	return (0);
}

int				printer_ptr(void *conv, va_list *vl, t_printf_buffer *buffer)
{
	void	*arg;
	size_t	arg_len;

	arg = va_arg(*vl, void *);
	arg_len = get_arg_len((unsigned long long)arg);
	if (((t_conv *)conv)->zero_padded)
		add_to_buffer_nstring(buffer, ((t_conv *)conv)->format->prepend,
				ft_strlen(((t_conv *)conv)->format->prepend));
	if (!((t_conv *)conv)->left_padded && ((t_conv *)conv)->field_width)
		print_padding(conv, arg_len
				+ ft_strlen(((t_conv *)conv)->format->prepend), buffer);
	if (!((t_conv *)conv)->zero_padded)
		add_to_buffer_nstring(buffer, ((t_conv *)conv)->format->prepend,
				ft_strlen(((t_conv *)conv)->format->prepend));
	if (((t_conv *)conv)->precision_set)
		print_precision(conv, arg_len, buffer);
	if (!((t_conv *)conv)->precision_set || ((t_conv *)conv)->precision || arg)
		ft_putullnbr_base_buffer((unsigned long long)arg, HEXA_STRING, buffer);
	if (((t_conv *)conv)->left_padded && ((t_conv *)conv)->field_width)
		print_padding(conv, arg_len
				+ ft_strlen(((t_conv *)conv)->format->prepend), buffer);
	return (0);
}
