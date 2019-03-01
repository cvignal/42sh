/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 07:36:11 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/01 15:29:44 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static int	options_echo(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j])
		{
			if (args[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int			builtin_echo(t_shell *shell, char **args)
{
	int	nl;
	int	i;

	nl = 1;
	(void)shell;
	if ((i = options_echo(args)) > 1)
		nl = 0;
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		++i;
	}
	if (nl)
		ft_printf("\n");
	return (0);
}
