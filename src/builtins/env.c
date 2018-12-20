/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 15:44:09 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/11 19:31:47 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	ft_disp_env(char **env)
{
	int	i;

	i = 0;
	if (!env || !*env)
		return ;
	while (env[i])
		ft_printf("%s\n", env[i++]);
}

char	**ft_clear_env(char **env)
{
	char	**ret;

	ft_deltab(&env);
	if (!(ret = (char**)malloc(sizeof(char*) * 1)))
		return (NULL);
	ret[0] = NULL;
	return (ret);
}

int		ft_env(char **args, const char **env, char *line)
{
	char	**cpy_env;

	if (!(cpy_env = copy_env(env)))
		return (0);
	if (!*args)
		ft_disp_env(cpy_env);
	if (ft_strequ(*args, "-i"))
	{
		cpy_env = ft_clear_env(cpy_env);
		args++;
	}
	if (ft_strchr(*args, '='))
	{
		cpy_env = ft_setenv(args, cpy_env);
		ft_env(args + 1, (const char**)cpy_env, line);
	}
	else
		ft_launch(args, &cpy_env, line);
	ft_deltab(&cpy_env);
	return (1);
}
