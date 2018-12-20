/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/18 07:51:48 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/25 12:18:24 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	mod_l(t_conv *conv)
{
	if (conv->type_mod == TYPE_MOD_L)
		conv->type_mod = TYPE_MOD_LL;
	else if (conv->type_mod == TYPE_MOD_NONE)
		conv->type_mod = TYPE_MOD_L;
	else if (conv->type_mod == TYPE_MOD_H)
		conv->type_mod = TYPE_MOD_NONE;
	else if (conv->type_mod == TYPE_MOD_HH)
		conv->type_mod = TYPE_MOD_H;
	else
		return (1);
	return (0);
}
