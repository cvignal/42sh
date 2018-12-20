/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 20:38:39 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/15 22:01:34 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "ast.h"

int		exec_or(t_shell *shell, t_ast *ast)
{
	if (ast->left->exec(shell, ast->left))
		return (ast->right->exec(shell, ast->right));
	return (0);
}

void	free_or(t_ast *ast)
{
	ast->left->del(ast->left);
	ast->right->del(ast->right);
	free(ast->data);
	free(ast);
}
