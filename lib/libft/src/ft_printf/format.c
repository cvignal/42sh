/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:10:46 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/14 18:21:59 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>

#include "ft_printf.h"
#include "libft.h"

static const t_format	g_formats[] =\
{
	{ &printer_string, NULL, sizeof(void *),
		{ TYPE_STRING, FORMAT_STRING }, NULL, 0},
	{ &printer_lstring, NULL, sizeof(void *),
		{ TYPE_LSTRING, FORMAT_LSTRING }, NULL, 0},
	{ &printer_ptr, NULL, sizeof(void *),
		{ TYPE_PTR, FORMAT_PTR }, PREPEND_PTR, 0},
	{ &printer_generic_number, DECIMAL_STRING, sizeof(int),
		{ TYPE_INT, FORMAT_INT }, NULL, 1 },
	{ &printer_generic_number, DECIMAL_STRING, sizeof(int),
		{ TYPE_INT, FORMAT_INT2 }, NULL, 1 },
	{ &printer_generic_number, DECIMAL_STRING, sizeof(long int),
		{ TYPE_INT2, FORMAT_INT_CAP }, NULL, 1 },
	{ &printer_generic_number, DECIMAL_STRING, sizeof(unsigned int),
		{ TYPE_UINT, FORMAT_UINT }, NULL, 0 },
	{ &printer_generic_number, DECIMAL_STRING, sizeof(unsigned long int),
		{ TYPE_INT2, FORMAT_UINT2 }, NULL, 0 },
	{ &printer_generic_number, OCTAL_STRING, sizeof(int),
		{ TYPE_UINT, FORMAT_OCTAL_INT }, NULL, 0 },
	{ &printer_generic_number, OCTAL_STRING, sizeof(long int),
		{ TYPE_INT2, FORMAT_OCTAL_INT2 }, NULL, 0 },
	{ &printer_generic_number, HEXA_STRING_CAP, sizeof(int),
		{ TYPE_UINT, FORMAT_HEXA_INT_CAP }, PREPEND_HEXA_CAP, 0 },
	{ &printer_generic_number, HEXA_STRING, sizeof(int),
		{ TYPE_UINT, FORMAT_HEXA_INT }, PREPEND_HEXA, 0 },
	{ &printer_character, NULL, sizeof(char),
		{ TYPE_CHARACTER, FORMAT_CHARACTER }, NULL, 0 },
	{ &printer_character, NULL, sizeof(wchar_t),
		{ TYPE_WCHARACTER, FORMAT_WCHARACTER }, NULL, 0 },
	{ &printer_double, DECIMAL_STRING, sizeof(double),
		{ TYPE_DOUBLE, FORMAT_DOUBLE }, NULL, 1 },
	{ &printer_double, DECIMAL_STRING, sizeof(double),
		{ TYPE_DOUBLE, FORMAT_DOUBLE2 }, NULL, 1 },
	{ &printer_none, NULL, 0, { TYPE_NONE, FORMAT_NONE }, NULL, 0 }
};

t_format	*new_format(char c)
{
	t_format	*format;

	format = malloc(sizeof(*format));
	if (!format)
		return (NULL);
	ft_bzero(format, sizeof(*format));
	format->desc.desc = c;
	return (format);
}

t_format	*get_format(char c)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_formats) / sizeof(*g_formats))
	{
		if (g_formats[i].desc.desc == c)
			return ((t_format *)g_formats + i);
		++i;
	}
	return (NULL);
}
