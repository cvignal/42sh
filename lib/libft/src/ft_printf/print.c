/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 12:30:05 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/07 09:41:52 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_printf.h"
#include "libft.h"

int				print_normal(const char *format, int *pos,
		t_printf_buffer *buffer)
{
	int			to_print;

	to_print = 0;
	while (format[*pos + to_print] && format[*pos + to_print] != CONV_START)
		++to_print;
	add_to_buffer_nstring(buffer, format + *pos, to_print);
	*pos += to_print;
	return (0);
}

int				print_conv(const char *format, int *pos, void *vl,
		t_printf_buffer *buffer)
{
	t_conv		conv;
	int			ret;

	ft_bzero(&conv, sizeof(conv));
	if (!*(format + ++(*pos)))
		return (0);
	while (conv_flags(format, pos, &conv)
			|| conv_field_width(format, pos, &conv, vl)
			|| conv_precision(format, pos, &conv, vl)
			|| conv_mod(format, pos, &conv))
		continue ;
	if (!(conv.format = get_format(*(format + *pos))) && *(format + *pos))
		conv.format = new_format(*(format + *pos));
	if (*(format + *pos))
		++(*pos);
	apply_modifiers(&conv);
	if (conv.format == NULL)
		return (0);
	if (!conv.format->printer)
		ret = printer_none(&conv, vl, buffer);
	else
		ret = conv.format->printer(&conv, vl, buffer);
	if (!conv.format->printer)
		free(conv.format);
	return (ret);
}
