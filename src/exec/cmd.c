/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:43:54 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/12 21:31:59 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"

int		exec_cmd(t_shell *shell, t_ast *ast)
{
	int	ret;

	if (shell->ctrlc)
		return (0);
	if (expand_redirs(shell, ast->redir_list, EXP_LEXER_MASK_ALL))
		return (1);
	if (prepare_redirs(shell, ast, ast))
	{
		ast->ret = 127;
		return (1);
	}
	ret = exec(shell, ast);
	reset_redirs(shell, ast);
	return (ret);
}

void	free_cmd(t_ast *ast)
{
	free_command(ast->data);
	free_ast(ast);
}
