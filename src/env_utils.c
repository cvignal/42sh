/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 10:09:55 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:50:09 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

char	**copy_env(char **env)
{
	char			**new_env;
	size_t			size_env;
	unsigned int	i;

	size_env = 0;
	while (env[size_env])
		++size_env;
	if (!(new_env = malloc(sizeof(*new_env) * (size_env + 1))))
		return (NULL);
	i = 0;
	while (i < size_env)
	{
		if (!(new_env[i] = ft_strdup(env[i])))
			return (NULL);
		++i;
	}
	new_env[i] = NULL;
	return (new_env);
}

char	**split_env_arg(char *arg)
{
	char	**res;
	int		i;

	if (!(res = malloc(sizeof(*res) * 2)))
		return (NULL);
	i = 0;
	res[0] = malloc(sizeof(*(res[0]) * (ft_strchr(arg, '=') - arg + 1)));
	if (!res[0])
		return (NULL);
	while (*arg && *arg != '=')
		res[0][i++] = *arg++;
	res[0][i] = 0;
	if (*arg)
	{
		++arg;
		i = 0;
		if (!(res[1] = malloc(sizeof(*(res[1]) * (ft_strlen(arg) + 1)))))
			return (NULL);
		while (*arg)
			res[1][i++] = *arg++;
		res[1][i] = 0;
	}
	return (res);
}

char	*get_env_value(t_shell *shell, char *name)
{
	int		i;
	size_t	len;

	if (!shell->env)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], name, len) && shell->env[i][len] == '=')
			return (ft_strchr(shell->env[i], '=') + 1);
		++i;
	}
	return (NULL);
}

int		remove_env_value(t_shell *shell, char *name)
{
	int	i;
	int	len;
	int	shift;

	if (!shell->env || !name)
		return (1);
	len = ft_strlen(name);
	shift = 0;
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], name, len) && shell->env[i][len] == '=')
		{
			free(shell->env[i]);
			shift = 1;
		}
		if (shift)
			shell->env[i] = shell->env[i + 1];
		++i;
	}
	return (!shift);
}
