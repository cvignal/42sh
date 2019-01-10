/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 16:20:01 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/28 16:21:53 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

int	expr_eq(t_shell *shell, char **args)
{
	(void)shell;
	if (ft_atoi(args[0]) == ft_atoi(args[2]))
		return (0);
	return (1);
}
