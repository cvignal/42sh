/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_cap.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 08:47:03 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/21 08:48:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	mod_l_cap(t_conv *conv)
{
	if (conv->type_mod == TYPE_MOD_NONE)
		conv->type_mod = TYPE_MOD_L_CAP;
	else
		return (1);
	return (0);
}
