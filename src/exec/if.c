/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 13:01:03 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/08 09:31:14 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"

int		exec_if(t_shell *shell, t_ast *ast)
{
	int	ret;

	ret = 0;
	redir_save(ast->redir_list, ast);
	prepare_redirs(shell, ast, ast);
	if (((t_ast *)ast->data)->exec(shell, ast->data) == 0)
		ret = ast->left->exec(shell, ast->left);
	else if (ast->right)
		ret = ast->right->exec(shell, ast->right);
	reset_redirs(ast);
	return (ret);
}

void	free_if(t_ast *ast)
{
	if (ast->right)
		ast->right->del(ast->right);
	if (ast->left)
		ast->left->del(ast->left);
	((t_ast *)ast->data)->del(ast->data);
	free_ast(ast);
}
