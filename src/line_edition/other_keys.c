/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 16:57:21 by cvignal           #+#    #+#             */
/*   Updated: 2019/01/29 15:27:13 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fill_line.h"
#include "shell.h"

int	ft_homekey(t_shell *shell)
{
	while (shell->line.cursor > 0)
		ft_leftkey(shell);
	return (0);
}

int	ft_endkey(t_shell *shell)
{
	while (shell->line.cursor < shell->line.len)
		ft_rightkey(shell);
	return (0);
}
