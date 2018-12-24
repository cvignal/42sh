/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:46:52 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:56:04 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int		exec_end(t_shell *shell, t_ast *ast)
{
	ast->left->exec(shell, ast->left);
	return (ast->right->exec(shell, ast->right));
}

void	free_end(t_ast *ast)
{
	ast->left->del(ast->left);
	ast->right->del(ast->right);
	free(ast->data);
	free(ast);
}
