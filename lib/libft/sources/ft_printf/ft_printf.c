/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 12:13:12 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/19 15:52:46 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list			vl;
	int				pos;
	t_printf_buffer	*buffer;
	int				ret;

	if (!format || !(buffer = create_buffer(1)))
		return (-1);
	pos = 0;
	ret = 0;
	va_start(vl, format);
	while (format[pos])
	{
		if (format[pos] == CONV_START)
		{
			if ((ret = print_conv(format, &pos, &vl, buffer)))
			{
				free_buffer(buffer);
				break ;
			}
		}
		else
			print_normal(format, &pos, buffer);
	}
	va_end(vl);
	return (ret ? -1 : (int)dump_buffer(buffer));
}
