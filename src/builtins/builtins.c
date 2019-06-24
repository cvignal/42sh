/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:07:42 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/24 19:02:11 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static const t_builtin_desc	g_builtin_desc[] =\
{
	{"bg", &builtin_bg},
	{"cd", &builtin_cd},
	{"echo", &builtin_echo},
	{"exit", &builtin_exit},
	{"export", &builtin_export},
	{"fc", &builtin_fc},
	{"fc", &builtin_fc},
	{"fg", &builtin_fg},
	{"hash", &builtin_hash},
	{"jobs", &builtin_jobs},
	{"set", &builtin_set},
	{"type", &builtin_type},
	{"test", &builtin_test},
	{"unset", &builtin_unset}
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
