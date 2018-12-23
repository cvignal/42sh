/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 07:36:11 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:52:40 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"

int	builtin_echo(t_shell *shell, char **args)
{
	int	nl;
	int	i;

	(void)shell;
	nl = 1;
	i = 1;
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
