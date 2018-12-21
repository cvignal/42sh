/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   none.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 11:54:02 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/24 11:29:54 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

#include "ft_printf.h"
#include "libft.h"

static size_t	print_padding(t_conv *conv, t_printf_buffer *buffer)
{
	unsigned int	i;

	i = 0;
	if (conv->field_width)
	{
		while (i < conv->field_width - 1)
		{
			if (conv->zero_padded && !conv->left_padded)
				add_to_buffer(buffer, '0');
			else
				add_to_buffer(buffer, ' ');
			++i;
		}
	}
	return (0);
}

int				printer_none(void *conv, va_list *vl, t_printf_buffer *buffer)
{
	(void)vl;
	if (!((t_conv *)conv)->left_padded)
		print_padding(conv, buffer);
	add_to_buffer(buffer, ((t_conv *)conv)->format->desc.desc);
	if (((t_conv *)conv)->left_padded)
		print_padding(conv, buffer);
	return (0);
}
