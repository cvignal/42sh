/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 23:20:53 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/11 19:07:31 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "libft.h"

static void	print_escaped_special(const char *var, unsigned int *begin,
		unsigned int *end)
{
	if (*end != *begin)
		write(STDOUT_FILENO, var + *begin, *end - *begin - 1);
	write(STDOUT_FILENO, "\\", 1);
	*begin = *end;
}

static void	print_escaped(const char *var)
{
	unsigned int	begin;
	unsigned int	end;
	int				equal_found;

	begin = 0;
	end = 0;
	equal_found = 0;
	while (var[end])
	{
		if (var[end] == '$' || var[end] == '"' || var[end] == '\\')
			print_escaped_special(var, &begin, &end);
		else if (!equal_found && var[end] == '=')
		{
			equal_found = 1;
			write(STDOUT_FILENO, var + begin, end - begin + 1);
			begin = end + 1;
			write(STDOUT_FILENO, "\"", 1);
		}
		++end;
	}
	if (end != begin)
		write(STDOUT_FILENO, var + begin, end - begin);
	write(STDOUT_FILENO, "\"\n", 2);
}

static int	print_env_dec(t_var *vars)
{
	t_var			*vars_array;
	unsigned int	i;

	if (!(vars_array = vars_to_array(vars)))
		return (1);
	i = 0;
	while (vars)
	{
		if (vars_array[i].exported)
		{
			ft_printf("export ");
			if (vars_array[i].set)
				print_escaped(vars_array[i].var);
			else
			{
				write(STDOUT_FILENO, vars_array[i].var,
						ft_strlen(vars_array[i].var));
				write(STDOUT_FILENO, "\n", 1);
			}
		}
		vars = vars->next;
		++i;
	}
	free(vars_array);
	return (0);
}

static int	args_parser(char **args)
{
	unsigned int	i;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		if (!ft_strcmp(args[i], "--"))
			return (i + 1);
		else if (ft_strcmp(args[i], "-p"))
		{
			ft_dprintf(STDERR_FILENO,
					"%s: export: %s invalid option\n",
					EXEC_NAME, args[i]);
			ft_dprintf(STDERR_FILENO, 
					"%s: usage: export [-p] [NAME[=VALUE] ...]\n",
					EXEC_NAME);
			return (-1);
		}
		++i;
	}
	return (i);
}

int			builtin_export(t_shell *shell, char **args)
{
	int		i;
	t_var	*var;
	int		ret;

	if ((i = args_parser(args)) < 0)
		return (1);
	if (!args[i])
		print_env_dec(shell->exec_vars);
	else
	{
		while (args[i])
		{
			ret = 0;
			if (ft_strchr(args[i], '='))
				ret = set_var_full(&shell->vars, args[i], 1);
			else if ((var = get_var(shell->vars, args[i])))
				var->exported = 1;
			else
				ret = set_var(&shell->vars, args[i], NULL, 1);
			if (ret)
				return (1);
			++i;
		}
	}
	return (0);
}
