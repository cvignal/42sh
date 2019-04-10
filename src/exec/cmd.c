/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:43:54 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 08:23:21 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"

static int	exec_cmd_internal(t_shell *shell, t_ast *ast)
{
	t_var	*tmp_vars;
	t_var	*backup;
	int		ret;

	tmp_vars = copy_vars(shell->vars);
	if (!tmp_vars)
		return (127);
	add_to_vars(&tmp_vars, ast->assignements);
	backup = shell->vars;
	shell->vars = tmp_vars;
	ret = exec(shell, ast);
	shell->vars = backup;
	free_vars(&tmp_vars);
	return (ret);
}

int			exec_cmd(t_shell *shell, t_ast *ast)
{
	int		ret;

	if (shell->ctrlc)
		return (0);
	if (expand_redirs(shell, ast->redir_list))
		return (1);
	if (prepare_redirs(shell, ast, ast))
	{
		ast->ret = 127;
		return (1);
	}
	ret = 0;
	if (((t_command *)ast->data)->args_len == 0)
		add_to_vars(&shell->vars, ast->assignements);
	else
		ret = exec_cmd_internal(shell, ast);
	reset_redirs(shell, ast);
	return (ret);
}

void		free_cmd(t_ast *ast)
{
	free_command(ast->data);
	free_ast(ast);
}
