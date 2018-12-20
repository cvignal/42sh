/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 09:54:50 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/10 12:50:31 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	**ft_unsetenv(char **args, char **env)
{
	int		i;
	char	**res;
	int		len;
	int		j;

	if (!ft_getenv(env, args[0]))
		return (env);
	if (!(res = (char **)malloc(sizeof(char *) * len_env(env))))
		return (NULL);
	i = 0;
	len = ft_strlen(args[0]);
	j = 0;
	while (env[i])
	{
		if (ft_strnequ(env[i], args[0], len))
			i++;
		else if (!(res[j++] = ft_strdup(env[i++])))
			return (NULL);
	}
	res[j] = NULL;
	ft_deltab(&env);
	return (res);
}
