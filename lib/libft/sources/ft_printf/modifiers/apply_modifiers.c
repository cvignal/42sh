/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_modifiers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 08:54:54 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/24 22:08:27 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdint.h>

#include "ft_printf.h"

static int	apply_modifiers_int(t_conv *conv)
{
	if (conv->type_mod == TYPE_MOD_H)
		conv->arg_size = sizeof(short);
	else if (conv->type_mod == TYPE_MOD_HH)
		conv->arg_size = sizeof(char);
	else if (conv->type_mod == TYPE_MOD_L)
		conv->arg_size = sizeof(long);
	else if (conv->type_mod == TYPE_MOD_LL)
		conv->arg_size = sizeof(long long);
	else if (conv->type_mod == TYPE_MOD_J)
		conv->arg_size = sizeof(intmax_t);
	else if (conv->type_mod == TYPE_MOD_Z)
		conv->arg_size = sizeof(size_t);
	else if (conv->type_mod != TYPE_MOD_NONE)
		return (1);
	return (0);
}

static int	apply_modifiers_double(t_conv *conv)
{
	if (conv->type_mod == TYPE_MOD_L_CAP)
		conv->arg_size = sizeof(long double);
	else if (conv->type_mod == TYPE_MOD_L)
		;
	else if (conv->type_mod != TYPE_MOD_NONE)
		return (1);
	return (0);
}

static int	apply_modifiers_character(t_conv *conv)
{
	if (conv->format->desc.type == TYPE_CHARACTER)
	{
		if (conv->type_mod == TYPE_MOD_L)
			conv->arg_size = sizeof(wchar_t);
		else if (conv->type_mod != TYPE_MOD_NONE)
			return (1);
	}
	return (0);
}

static int	apply_modifiers_string(t_conv *conv)
{
	if (conv->type_mod == TYPE_MOD_L)
		conv->format = get_format(FORMAT_LSTRING);
	else if (conv->type_mod != TYPE_MOD_NONE)
		return (1);
	return (0);
}

int			apply_modifiers(t_conv *conv)
{
	if (!conv->format)
		return (0);
	conv->arg_size = conv->format->arg_size;
	if (conv->format->desc.type == TYPE_INT
			|| conv->format->desc.type == TYPE_UINT)
		return (apply_modifiers_int(conv));
	else if (conv->format->desc.type == TYPE_DOUBLE)
		return (apply_modifiers_double(conv));
	else if (conv->format->desc.type == TYPE_CHARACTER
			|| conv->format->desc.type == TYPE_WCHARACTER)
		return (apply_modifiers_character(conv));
	else if (conv->format->desc.type == TYPE_STRING)
		return (apply_modifiers_string(conv));
	return (0);
}
