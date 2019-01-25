/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:01:29 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/25 15:24:30 by gchainet         ###   ########.fr       */
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
		if (instr->fds[i] >= 0)
			dup2(instr->fds[i], i);
		else if (instr->fds[i] == -2)
			close(i);
		++i;
	}
	return (0);
}
