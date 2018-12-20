/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 18:39:59 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/10 17:18:30 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**ft_add_variable(char **var, char **my_env)
{
	char	**res;
	int		i;

	i = 0;
	while (my_env[i])
		i++;
	if (!(res = (char **)malloc(sizeof(char *) * (i + 2))))
		return (NULL);
	i = 0;
	while (my_env[i])
	{
		if (!(res[i] = ft_strdup(my_env[i])))
			return (NULL);
		i++;
	}
	res[i] = ft_strjoin(var[0], "=");
	res[i] = ft_strjoin_free(res[i], var[1], 1);
	res[i + 1] = NULL;
	ft_deltab(&my_env);
	ft_deltab(&var);
	return (res);
}

char	**ft_setenv(char **args, char **my_env)
{
	int		i;
	int		len;
	char	**var;

	i = 0;
	if (!(var = ft_strsplit(*args, "=")) || !*var || !var[1] || var[2])
		return (my_env);
	len = (int)ft_strlen(var[0]);
	while (my_env[i])
	{
		if (!ft_strncmp(my_env[i], var[0], len))
		{
			ft_strdel(&my_env[i]);
			my_env[i] = ft_strjoin(var[0], "=");
			my_env[i] = ft_strjoin_free(my_env[i], var[1], 1);
			ft_deltab(&var);
			return (my_env);
		}
		i++;
	}
	return (ft_add_variable(var, my_env));
}
