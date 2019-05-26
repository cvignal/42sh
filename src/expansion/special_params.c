/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:35:55 by marin             #+#    #+#             */
/*   Updated: 2019/05/25 14:47:42 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static const char	g_special_params[5] = \
{
	SPECIAL_PARAM_AT,
		SPECIAL_PARAM_STAR,
		SPECIAL_PARAM_ZERO,
		SPECIAL_PARAM_BANG,
		SPECIAL_PARAM_HASH
};

int			is_special_param(char name)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_special_params) / sizeof(*g_special_params))
	{
		if (g_special_params[i] == name)
			return (1);
		++i;
	}
	return (0);
}
