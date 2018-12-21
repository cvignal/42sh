/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 12:34:58 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/25 10:22:18 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <wchar.h>

#include "libft.h"
#include "ft_printf.h"

static int		print_padding(t_conv *conv, wchar_t c, t_printf_buffer *buffer)
{
	size_t		i;
	size_t		size;

	if (conv->arg_size == sizeof(wchar_t))
		size = ft_char_size_utf8((unsigned int)c);
	else
		size = 1;
	if (size > sizeof(wchar_t))
		return (1);
	i = 0;
	while (i + size < conv->field_width)
	{
		if (conv->zero_padded)
			add_to_buffer(buffer, '0');
		else
			add_to_buffer(buffer, ' ');
		++i;
	}
	return (0);
}

int				printer_character(void *conv, va_list *vl,
		t_printf_buffer *buffer)
{
	wchar_t	arg;

	arg = va_arg(*vl, wint_t);
	if (!((t_conv *)conv)->left_padded)
	{
		if (print_padding(conv, arg, buffer))
			return (1);
	}
	if (((t_conv *)conv)->arg_size == sizeof(wchar_t))
		ft_putcharw_buffer(buffer, arg);
	else if (((t_conv *)conv)->arg_size == sizeof(char))
		add_to_buffer(buffer, (char)arg);
	if (((t_conv *)conv)->left_padded)
		print_padding(conv, arg, buffer);
	return (0);
}
