/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 20:38:39 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 05:32:32 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int		exec_or(t_shell *shell, t_ast *ast)
{
	ast->left->exec(shell, ast->left);
	wait_loop(ast->left);
	if (ast->left->ret != 0)
	{
		ast->right->exec(shell, ast->right);
		wait_loop(ast->right);
		return (ast->right->ret);
	}
	return (0);
}

void	free_or(t_ast *ast)
{
	ast->left->del(ast->left);
	ast->right->del(ast->right);
	free(ast);
}
