/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 10:26:43 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/25 15:34:12 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"

int	reset_redirs(t_ast *instr)
{
	unsigned int	i;

	if (instr->left)
		reset_redirs(instr->left);
	i = 0;
	while (i < 10)
	{
		if (instr->fds[i] != -1)
			dup2(instr->old_fds[i], i);
		++i;
	}
	if (instr->right)
		reset_redirs(instr->right);
	return (0);
}
