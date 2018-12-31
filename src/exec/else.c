/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   else.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 13:05:23 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 14:47:22 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int	exec_else(t_shell *shell, t_ast *ast)
{
	if (ast->left)
		return (ast->left->exec(shell, ast->left));
	return (0);
}

void	free_else(t_ast *ast)
{
	if (ast->left)
		ast->left->del(ast->left);
	free(ast);
}
