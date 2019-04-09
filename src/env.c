/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 09:04:48 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/09 09:10:38 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"

t_var	*copy_env(const char **env)
{
	t_var	*res;
	t_var	*var;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		if (!(var = create_var(env[i])))
		{
			while (res)
			{
				free(res);
				res = res->next;
			}
			return (NULL);
		}
		var->next = res;
		res = var;
		++i;
	}
	return (var);
}

void	free_vars(t_shell *shell)
{
	t_var	*i;
	t_var	*next;

	i = shell->vars;
	while (i)
	{
		next = i->next;
		free(i);
		i = next;
	}
	shell->vars = NULL;
}
