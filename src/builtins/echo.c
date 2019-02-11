/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 07:36:11 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/11 11:34:17 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	builtin_echo(t_shell *shell, char **args)
{
	int	nl;
	int	i;

	nl = 1;
	i = 1;
	(void)shell;
	if (args[i] && !ft_strcmp(args[i], "-n"))
	{
		nl = 0;
		++i;
	}
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
