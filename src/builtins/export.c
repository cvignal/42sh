/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 23:20:53 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/04 00:23:01 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "libft.h"

static void	print_escaped(const char *var)
{
	unsigned int	begin;
	unsigned int	end;
	size_t			len;

	len = ft_strlen(var);
	begin = 0;
	end = 0;
	while (begin < len)
	{
		if (!var[end])
		{
			write(STDOUT_FILENO, var + begin, end - begin);
			break ;
		}
		else if (var[end] == '$' || var[end] == '"')
		{
			if (end != begin)
				write(STDOUT_FILENO, var + begin, end - begin - 1);
			write(STDOUT_FILENO, "\\", 1);
			begin = end;
		}
		++end;
	}
	write(STDOUT_FILENO, "\n", 1);
}

static void	print_env_dec(t_shell *shell)
{
	t_var	*var;

	var = shell->exec_vars;
	while (var)
	{
		if (var->exported)
		{
			ft_printf("export ");
			print_escaped(var->var);
		}
		var = var->next;
	}
}

int			builtin_export(t_shell *shell, char **args)
{
	size_t	ac;
	int		i;
	t_var	*var;

	ac = 0;
	while (args[ac])
		++ac;
	if (ac == 2 && !ft_strcmp(args[1], "-p"))
		print_env_dec(shell);
	else
	{
		i = 1;
		if (ft_strchr(args[i], '='))
			return (set_var_full(&shell->vars, args[i], 1));
		else if ((var = get_var(shell->vars, args[i])))
			var->exported = 1;
		else
			return (set_var(&shell->vars, args[i], NULL, 1));
			
	}
	return (0);
}
