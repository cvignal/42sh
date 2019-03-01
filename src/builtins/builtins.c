/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:07:42 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/01 10:17:38 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static const t_builtin_desc	g_builtin_desc[] =\
{
	{"echo", &builtin_echo},
	{"env", &builtin_env},
	{"setenv", &builtin_setenv},
	{"unsetenv", &builtin_unsetenv},
	{"exit", &builtin_exit},
	{"cd", &builtin_cd},
	{"type", &builtin_type}
};

t_builtin	is_builtin(char *cmd)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_builtin_desc) / sizeof(*g_builtin_desc))
	{
		if (!ft_strcmp(g_builtin_desc[i].desc, cmd))
			return (g_builtin_desc[i].builtin);
		++i;
	}
	return (NULL);
}
