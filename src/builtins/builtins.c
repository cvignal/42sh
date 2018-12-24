/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:07:42 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:51:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"

static const t_builtin_desc	g_builtin_desc[] =
{
	{"echo", &builtin_echo},
	{"env", &builtin_env},
	{"setenv", &builtin_setenv},
	{"unsetenv", &builtin_unsetenv},
	{"exit", &builtin_exit},
	{"cd", &builtin_cd},
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
