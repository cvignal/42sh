/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 21:40:25 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/15 21:40:49 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "ast.h"

int		exec_and(t_shell *shell, t_ast *ast)
{
	if (!ast->left->exec(shell, ast->left))
		return (ast->right->exec(shell, ast->right));
	return (1);
}

void	free_and(t_ast *ast)
{
	ast->left->del(ast->left);
	ast->right->del(ast->right);
	free(ast->data);
	free(ast);
}
