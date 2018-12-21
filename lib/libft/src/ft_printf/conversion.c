/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 10:57:10 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/07 12:45:49 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "ft_printf.h"
#include "libft.h"

int		conv_flags(const char *format, int *pos, t_conv *conv)
{
	t_flag_op	flag_op;

	if ((flag_op = get_flag_op(*(format + *pos))))
	{
		flag_op(conv);
		++(*pos);
		return (1);
	}
	return (0);
}

int		conv_field_width(const char *format, int *pos, t_conv *conv,
		va_list *ap)
{
	if (ft_isdigit(*(format + *pos)))
	{
		conv->field_width = ft_atoi(format + *pos);
		while (ft_isdigit(*(format + *pos)))
			++(*pos);
		return (1);
	}
	else if (*(format + *pos) == '*')
	{
		conv->field_width = va_arg(*ap, int);
		++(*pos);
	}
	return (0);
}

int		conv_precision(const char *format, int *pos, t_conv *conv, va_list *ap)
{
	if (*(format + *pos) == PRECISION_PERIOD)
	{
		conv->precision_set = 1;
		++(*pos);
		if (*(format + *pos) == '*')
		{
			conv->precision = va_arg(*ap, int);
			++(*pos);
		}
		else
		{
			conv->precision = ft_atoi(format + *pos);
			while (ft_isdigit(*(format + *pos)))
				++(*pos);
		}
		return (1);
	}
	return (0);
}

int		conv_mod(const char *format, int *pos, t_conv *conv)
{
	t_conv_mod	conv_mod;

	if ((conv_mod = get_conv_mod(*(format + *pos))))
	{
		conv_mod(conv);
		++(*pos);
		return (1);
	}
	return (0);
}
