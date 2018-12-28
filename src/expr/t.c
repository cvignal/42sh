/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:44:54 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/27 16:47:04 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "21sh.h"
#include "libft.h"

int	expr_t(t_shell *shell, char **args)
{
	(void)shell;
	return (!isatty(ft_atoi(args[1])));
}
