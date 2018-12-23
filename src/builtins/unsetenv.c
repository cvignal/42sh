/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 08:22:56 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 19:03:43 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"

static int	is_target(char *s, char *target)
{
	int	i;

	i = 0;
	while (s[i] && target[i] && s[i] != '=')
	{
		if (s[i] != target[i])
			return (0);
		++i;
	}
	return (!target[i] && s[i] == '=');
}

static int	exit_error(const char *msg)
{
	ft_dprintf(2, "%s: unsetenv: %s\n", EXEC_NAME, msg);
	return (1);
}

static int	replace_env(t_shell *shell, char **new_env, int env_size,
		char *target)
{
	int	step;
	int	i;

	i = 0;
	step = 0;
	while (i < env_size)
	{
		if (!is_target(shell->env[i], target))
			new_env[i - step] = shell->env[i];
		else
		{
			free(shell->env[i]);
			step = 1;
		}
		++i;
	}
	new_env[i - step] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

int			builtin_unsetenv(t_shell *shell, char **args)
{
	int		env_size;
	char	**new_env;
	size_t	arg_count;

	arg_count = 0;
	while (args[arg_count])
		++arg_count;
	if (arg_count > 2)
		return (exit_error("too many arguments"));
	else if (arg_count < 2)
		return (exit_error("usage: unsetenv var"));
	env_size = 0;
	while (shell->env[env_size])
		++env_size;
	if (!(new_env = malloc(sizeof(*new_env) * (env_size + 1))))
		return (1);
	return (replace_env(shell, new_env, env_size, args[1]));
}
