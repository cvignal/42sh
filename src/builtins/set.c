/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 00:53:07 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/26 16:08:03 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "libft.h"

static int	should_quote(const char *var)
{
	unsigned int	i;
	unsigned int	j;
	size_t			len;

	len = ft_strlen(QUOTABLE_CHARS);
	i = 0;
	while (var[i])
	{
		j = 0;
		while (j < len)
		{
			if (var[i] == QUOTABLE_CHARS[j])
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

static void	print_var_set(const char *var)
{
	int	pos;

	pos = 0;
	while (var[pos])
	{
		if (var[pos] == '=')
		{
			write(STDOUT_FILENO, var, pos + 1);
			if (should_quote(var + pos))
				ft_printf("'%s'\n", var + pos + 1);
			else
				ft_printf("%s\n", var + pos + 1);
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
		if (!is_special_param(var->var[0]))
			print_var_set(var->var);
		var = var->next;
	}
	return (0);
}
