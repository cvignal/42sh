/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_number_padding.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 05:33:06 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/24 08:08:09 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

size_t				print_padding_left(t_conv *c, size_t max_len,
		long long arg, t_printf_buffer *buffer)
{
	int		i;
	size_t	ret;

	ret = 0;
	i = 0;
	print_sign(c, arg, 0, buffer);
	ret += print_prepend(c, arg, 0, buffer);
	while (((int)c->field_width) - ((int)max_len) - (int)ret - i > 0
			&& !c->left_padded)
	{
		if (c->zero_padded && !c->left_padded && !c->precision_set)
			add_to_buffer(buffer, '0');
		else
			add_to_buffer(buffer, ' ');
		++i;
	}
	print_sign(c, arg, 1, buffer);
	print_prepend(c, arg, 1, buffer);
	return (0);
}

size_t				print_padding_right(t_conv *c, size_t max_len,
		long long arg, t_printf_buffer *buffer)
{
	int		i;
	size_t	ret;

	if (c->alternate && c->format->prepend && arg)
		ret = ft_strlen(c->format->prepend);
	else
		ret = 0;
	i = 0;
	while (((int)c->field_width) - ((int)max_len) - (int)ret - i > 0
			&& c->left_padded)
	{
		if (c->zero_padded && !c->left_padded && !c->precision_set)
			add_to_buffer(buffer, '0');
		else
			add_to_buffer(buffer, ' ');
		++i;
	}
	return (0);
}
