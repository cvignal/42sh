/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:46:52 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 20:20:24 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int		exec_end(t_shell *shell, t_ast *ast)
{
	prepare_redirs(shell, ast, ast);
	ast->left->exec(shell, ast->left);
	wait_loop(ast->left);
	ast->right->exec(shell, ast->right);
	wait_loop(ast->right);
	return (ast->right->ret);
}

void	free_end(t_ast *ast)
{
	if (ast->left)
		ast->left->del(ast->left);
	if (ast->right)
		ast->right->del(ast->right);
	free_ast(ast);
}
