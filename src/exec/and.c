/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 21:40:25 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/05 13:32:07 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int		exec_and(t_shell *shell, t_ast *ast)
{
	ast->left->exec(shell, ast->left);
	wait_loop(ast->left);
	if (ast->left->ret == 0)
	{
		ast->right->exec(shell, ast->right);
		wait_loop(ast->right);
		return (ast->right->ret);
	}
	return (1);
}

void	free_and(t_ast *ast)
{
	ast->left->del(ast->left);
	ast->right->del(ast->right);
	free(ast->data);
	free(ast);
}
