/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:43:54 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 06:12:50 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"

static void	add_to_vars(t_shell *shell, t_var *vars)
{
	t_var	*iter;

	if (vars)
	{
		iter = vars;
		while (iter->next)
		{
			iter->exported = 0;
			iter = iter->next;
		}
		iter->next = shell->vars;
		shell->vars = vars;
	}
}

static void	remove_from_vars(t_shell *shell, t_var *vars, t_var *old)
{
	while (shell->vars && shell->vars != old)
	{
		shell->vars = shell->vars->next;
		free(vars);
		vars = shell->vars;
	}
}

int		exec_cmd(t_shell *shell, t_ast *ast)
{
	int		ret;
	t_var	*old_vars;

	if (shell->ctrlc)
		return (0);
	if (expand_redirs(shell, ast->redir_list))
		return (1);
	if (prepare_redirs(shell, ast, ast))
	{
		ast->ret = 127;
		return (1);
	}
	old_vars = shell->vars;
	add_to_vars(shell, ast->assignements);
	if (((t_command *)ast->data)->args_len)
	{
		ret = exec(shell, ast);
		remove_from_vars(shell, ast->assignements, old_vars);
	}
	reset_redirs(shell, ast);
	return (ret);
}

void	free_cmd(t_ast *ast)
{
	free_command(ast->data);
	free_ast(ast);
}
