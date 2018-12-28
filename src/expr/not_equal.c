/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   not_equal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 11:53:56 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/28 11:58:37 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "libft.h"

int	expr_not_equal(t_shell *shell, char **args)
{
	(void)shell;
	if (ft_strcmp(args[0], args[2]))
		return (0);
	return (1);
}
