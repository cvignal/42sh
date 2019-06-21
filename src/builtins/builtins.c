/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:07:42 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/23 22:56:39 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static const t_builtin_desc	g_builtin_desc[] =\
{
	{"cd", &builtin_cd},
	{"echo", &builtin_echo},
	{"setenv", &builtin_setenv},
	{"unsetenv", &builtin_unsetenv},
	{"exit", &builtin_exit},
	{"fc", &builtin_fc},
	{"hash", &builtin_hash},
	{"fc", &builtin_fc},
	{"jobs", &builtin_jobs},
	{"fg", &builtin_fg},
	{"bg", &builtin_bg},
	{"type", &builtin_type},
	{"unset", &builtin_unset},
};

t_builtin	is_builtin(char *cmd)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_builtin_desc) / sizeof(*g_builtin_desc))
	{
		if (ft_strequ(g_builtin_desc[i].desc, cmd))
			return (g_builtin_desc[i].builtin);
		++i;
	}
	return (NULL);
}
