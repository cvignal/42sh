/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:57:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 08:07:06 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "parser.h"
#include "ast.h"

int		exec_while(t_shell *shell, t_ast *ast)
{
	int	ret;
	int	cont;

	ret = 0;
	cont = 1;
	while (cont)
	{
		((t_ast *)ast->data)->exec(shell, ast->data);
		wait_loop(ast->data);
		if (((t_ast *)ast->data)->ret == 0)
			ret = ast->left->exec(shell, ast->left);
		else
			cont = 1;
	}
	return (ret);
}

void	free_while(t_ast *ast)
{
	if (ast->left)
		ast->left->del(ast->left);
	free_ast(ast);
}
