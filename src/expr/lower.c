/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lower.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 11:56:37 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/28 11:57:35 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	expr_lower(t_shell *shell, char **args)
{
	(void)shell;
	if (ft_strcmp(args[0], args[2]) < 0)
		return (0);
	return (1);
}
