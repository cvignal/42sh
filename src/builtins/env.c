/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 07:44:20 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 03:41:37 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "libft.h"

static void	print_env(t_var *vars)
{
	while (vars)
	{
		if (vars->exported)
			ft_printf("%s\n", vars->var);
		vars = vars->next;
	}
}

static int	create_tmp_env_var(t_var **vars, char *name, char *value,
		const char *arg)
{
	size_t	len;
	char	*pos_eq;

	pos_eq = ft_strchr(arg, '=');
	len = pos_eq - arg - 1;
	if (len > VAR_MAX)
	{
		ft_dprintf(STDERR_FILENO, "%s: variable name too long\n", EXEC_NAME);
		return (1);
	}
	ft_strncat(name, arg, len);
	len = ft_strlen(pos_eq + 1);
	if (len > VAR_MAX)
	{
		ft_dprintf(STDERR_FILENO, "%s: variable content too long\n", EXEC_NAME);
		return (1);
	}
	ft_strncat(value, pos_eq + 1, len);
	if (set_var(vars, name, value, 1))
		return (1);
	return (0);
}

static int	set_tmp_env_vars(t_var **vars, int *i, char **args)
{
	char	var_name[VAR_MAX + 1];
	char	var_value[VAR_MAX + 1];

	while (args[*i] && ft_strchr(args[*i], '='))
	{
		var_name[0] = 0;
		var_value[0] = 0;
		if (create_tmp_env_var(vars, var_name, var_value, args[*i]))
			return (1);
		++(*i);
	}
	return (0);
}

int			builtin_env(t_shell *shell, char **args)
{
	int		i;
	t_var	*tmp_env;

	if (!(tmp_env = copy_env_from_vars(shell->vars)))
		return (1);
	if ((i = builtin_env_get_opts(args, &tmp_env)) == -1)
		return (1);
	if (set_tmp_env_vars(&tmp_env, &i, args))
		return (1);
	if (args[i])
		exec_from_char(shell, tmp_env, args + i);
	else if (tmp_env)
		print_env(tmp_env);
	free_vars(&tmp_env);
	return (0);
}
