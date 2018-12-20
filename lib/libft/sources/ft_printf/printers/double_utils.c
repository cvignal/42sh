/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 20:10:26 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/26 10:40:47 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	double_len(long double arg)
{
	size_t	len;

	len = 0;
	if (!(int)arg)
		return (1);
	while ((int)arg && !(arg != arg))
	{
		arg /= 10;
		++len;
	}
	return (len);
}

size_t			print_flags_double_left(t_conv *conv, long double nbr,
		size_t len, t_printf_buffer *buffer)
{
	(void)len;
	if (conv->zero_padded && !conv->left_padded)
	{
		if (!conv->sign && conv->space && nbr >= 0)
		{
			add_to_buffer(buffer, ' ');
			return (1);
		}
		else if (nbr >= 0 && conv->sign)
		{
			add_to_buffer(buffer, '+');
			return (1);
		}
	}
	return (0);
}

size_t			print_flags_double_right(t_conv *conv, long double nbr,
		size_t len, t_printf_buffer *buffer)
{
	(void)len;
	if (!(conv->zero_padded && !conv->left_padded))
	{
		if (!conv->sign && conv->space && nbr >= 0 && nbr >= 0)
		{
			add_to_buffer(buffer, ' ');
			return (1);
		}
		else if (nbr >= 0 && conv->sign)
		{
			add_to_buffer(buffer, '+');
			return (1);
		}
	}
	return (0);
}

size_t			print_padding_double(t_conv *conv, size_t len,
		t_printf_buffer *buffer)
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
	return (0);
}

int				get_padding_length_double(t_conv *conv, long double nbr)
{
	int		padding;
	size_t	nbr_len;

	padding = (int)conv->field_width;
	nbr_len = double_len(nbr);
	if (!nbr_len)
		return (-1);
	padding -= nbr_len;
	if (!conv->sign && conv->space && nbr >= 0)
		--padding;
	else if (conv->sign && nbr >= 0)
		--padding;
	if (conv->precision_set)
		padding -= conv->precision + 1;
	else
		padding -= 7;
	return (padding > 0 ? padding : 0);
}
