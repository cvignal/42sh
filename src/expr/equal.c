/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 11:50:19 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/28 11:52:30 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	expr_equal(t_shell *shell, char **args)
{
	(void)shell;
	if (!ft_strcmp(args[0], args[2]))
		return (0);
	return (1);
}
