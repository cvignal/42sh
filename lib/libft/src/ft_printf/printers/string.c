/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 12:21:16 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/25 11:19:07 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

#include "libft.h"
#include "ft_printf.h"

static int	print_space(t_conv *conv, size_t len, t_printf_buffer *buffer)
{
	int	i;

	i = 0;
	while (len + i < conv->field_width)
	{
		if (conv->zero_padded && !conv->left_padded)
			add_to_buffer(buffer, '0');
		else
			add_to_buffer(buffer, ' ');
		++i;
	}
	return (i);
}

int			printer_string(void *conv, va_list *vl, t_printf_buffer *buffer)
{
	size_t	len;
	char	*arg;

	arg = va_arg((*vl), char *);
	if (((t_conv *)conv)->precision_set)
	{
		if (arg)
			len = MIN(ft_strlen(arg), ((t_conv *)conv)->precision);
		else
			len = MIN(ft_strlen(NULL_PRINT), ((t_conv *)conv)->precision);
	}
	else
		len = ft_strlen(arg ? arg : NULL_PRINT);
	if (!((t_conv *)conv)->left_padded)
		print_space(conv, len, buffer);
	add_to_buffer_nstring(buffer, arg ? arg : NULL_PRINT, len);
	if (((t_conv *)conv)->left_padded)
		print_space(conv, len, buffer);
	return (0);
}
