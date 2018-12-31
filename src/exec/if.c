/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 13:01:03 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/29 17:41:17 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "ast.h"

int		exec_if(t_shell *shell, t_ast *ast)
{
	if (((t_ast *)ast->data)->exec(shell, ast->data) == 0)
		return (ast->left->exec(shell, ast->left));
	else if (ast->right)
		return (ast->right->exec(shell, ast->right));
	return (0);
}

void	free_if(t_ast *ast)
{
	if (ast->right)
		ast->right->del(ast->right);
	if (ast->left)
		ast->left->del(ast->left);
	((t_ast *)ast->data)->del(ast->data);
	free(ast);
}
