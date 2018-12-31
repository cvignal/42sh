/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:57:58 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 18:28:22 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "parser.h"
#include "ast.h"

int		exec_while(t_shell *shell, t_ast *ast)
{
	int	ret;

	ret = 0;
	while (((t_ast *)ast->data)->exec(shell, ast->data) == 0)
		ret = ast->left->exec(shell, ast->left);
	return (ret);
}

void	free_while(t_ast *ast)
{
	if (ast->left)
		ast->left->del(ast->left);
	free(ast);
}
