/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 03:02:32 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 14:40:09 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "arithmetic.h"

int	exec_ari_or(t_shell *shell, struct s_ast *ast)
{
	ast->left->exec(shell, ast->left);
	if (!ast->left->data)
		return (exec_ari_fail(ast));
	if (ft_atoi(ast->left->data))
	{
		ast->right->exec(shell, ast->right);
		if (!ast->right->data)
			return (exec_ari_fail(ast));
		ast->ret = !!ft_atoi(ast->right->data);
	}
	else
		ast->ret = 1;
	free(ast->data);
	if (!(ast->data = ft_itoa(ast->ret)))
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		ast->ret = 1;
		return (1);
	}
	return (0);
}
