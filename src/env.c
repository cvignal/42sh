/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 12:13:41 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/16 12:45:22 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "libft.h"

static char	*create_env_var(const char *var, const char *value)
{
	char	*new_env_var;
	size_t	size_var;
	size_t	size_value;

	size_var = ft_strlen(var);
	size_value = ft_strlen(value);
	new_env_var = malloc(sizeof(*new_env_var) * (size_var + size_value + 2));
	if (!new_env_var)
		return (NULL);
	ft_memcpy(new_env_var, var, size_var);
	new_env_var[size_var] = '=';
	ft_memcpy(new_env_var + size_var + 1, value, size_value);
	new_env_var[size_var + 1 + size_value] = 0;
	return (new_env_var);
}

static int	add_to_env(t_shell *shell, const char *var, const char *value)
{
	size_t			env_size;
	char			**new_env;
	char			*new_env_var;

	env_size = 0;
	if (shell->env)
		while (shell->env[env_size])
			++env_size;
	if (!(new_env = malloc(sizeof(*new_env) * (env_size + 2))))
		return (1);
	if (!(new_env_var = create_env_var(var, value)))
	{
		free(new_env);
		return (1);
	}
	ft_memcpy(new_env, shell->env, env_size * sizeof(*new_env));
	new_env[env_size] = new_env_var;
	new_env[env_size + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

static int	change_env(char **env, const char *var, const char *value)
{
	char	*new_env_var;

	if (!(new_env_var = create_env_var(var, value)))
		return (1);
	free(*env);
	*env = new_env_var;
	return (0);
}

void		remove_env(t_shell *shell)
{
	int		i;

	if (shell->env)
	{
		i = 0;
		while (shell->env[i])
			free(shell->env[i++]);
		free(shell->env);
	}
	shell->env = NULL;
}

int			set_env_var(t_shell *shell, const char *var, const char *value)
{
	int		i;
	size_t	var_len;

	var_len = ft_strlen(var);
	i = 0;
	if (!shell->env)
		return (add_to_env(shell, var, value));
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], var, var_len)
				&& shell->env[i][var_len] == '=')
			return (change_env(shell->env + i, var, value));
		++i;
	}
	return (add_to_env(shell, var, value));
}
