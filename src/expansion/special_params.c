/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:35:55 by marin             #+#    #+#             */
/*   Updated: 2019/05/27 23:33:51 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <unistd.h>

static const char	g_special_params[6] = \
{
	SPECIAL_PARAM_AT,
		SPECIAL_PARAM_STAR,
		SPECIAL_PARAM_ZERO,
		SPECIAL_PARAM_BANG,
		SPECIAL_PARAM_DOLLAR,
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

char	*get_special_param_value(char *name, t_shell *shell)
{
	if (!ft_strcmp(name, "$"))
		return (ft_itoa((int)getpid()));
	if (!ft_strcmp(name, "#"))
		return (ft_itoa(shell->arg_file ? shell->arg_file->argc : 0));
	return "hello";

}
