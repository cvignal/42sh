/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:35:26 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/11 13:48:12 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"

int	expand_home(t_shell *shell, char *arg, int *error)
{
	char	*home;

	if (arg[0] == '~')
	{
		home = get_env_value(shell, "HOME");
		if (home)
		{
			while (*home)
			{
				if (add_to_exp_buff(&shell->exp_lexer.buffer, *home))
				{
					*error = 1;
					return (-1);
				}
				++home;
			}
		}
		return (1);
	}
	return (0);
}
