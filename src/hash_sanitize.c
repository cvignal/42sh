/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_sanitize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 13:29:44 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 03:24:06 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"

static void		sanitize_hash_entry(t_shell *shell, t_hbt *node)
{
	char		*cmd;

	if (node)
	{
		cmd = find_command(shell->vars, node->bin);
		if (node->path)
		{
			if (!cmd)
			{
				free(node->path);
				node->path = NULL;
			}
			else
				free(cmd);
		}
		else
		{
			if (cmd)
				node->path = cmd;
		}
		sanitize_hash_entry(shell, node->left);
		sanitize_hash_entry(shell, node->right);
	}
}

void			sanitize_hash(t_shell *shell)
{
	unsigned int	i;

	i = 0;
	while (i < HASH_TABLE_SIZE)
		sanitize_hash_entry(shell, shell->hash_table[i++]);
}
