/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 00:53:07 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/04 01:15:09 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "libft.h"

static void	print_var_set(const char *var)
{
	int	pos;

	pos = 0;
	while (var[pos])
	{
		if (var[pos] == '=')
		{
			write(STDOUT_FILENO, var, pos + 1);
			if (ft_strchr(var + pos, '$') || ft_strchr(var + pos, '\\')
					|| ft_strchr(var + pos, '"'))
				ft_printf("'%s'\n", var + pos + 1);
			else
				ft_printf("%s\n", var + pos);
			return ;
		}
		++pos;
	}
	ft_printf("%s\n", var);
}

int			builtin_set(t_shell *shell, char **args)
{
	t_var	*var;

	(void)args;
	var = shell->exec_vars;
	while (var)
	{
		if (var->set)
			print_var_set(var->var);
		var = var->next;
	}
	return (0);
}
