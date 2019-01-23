/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:01:29 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/23 12:31:57 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "ast.h"

int		apply_redirs(t_shell *shell, t_ast *instr)
{
	unsigned int	i;

	(void)shell;
	i = 0;
	while (i < 10)
	{
		if (instr->fds[i] != -1)
			dup2(instr->fds[i], i);
		++i;
	}
	return (0);
}
