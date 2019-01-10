/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 11:59:00 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/28 12:00:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	expr_sup(t_shell *shell, char **args)
{
	(void)shell;
	if (ft_strcmp(args[0], args[2]) > 0)
		return (0);
	return (1);
}
