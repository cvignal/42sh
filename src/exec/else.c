/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 13:05:23 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 08:03:44 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"

int		exec_else(t_shell *shell, t_ast *ast)
{
	if (ast->left)
		return (ast->left->exec(shell, ast->left));
	return (0);
}

void	free_else(t_ast *ast)
{
	if (ast->left)
		ast->left->del(ast->left);
	free_ast(ast);
}
