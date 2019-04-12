/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:43:54 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/12 12:11:35 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"

static int	set_assignements(t_shell *shell, t_ast *ast, t_var **vars)
{
	t_var	*iter;
	char	*expanded;
	int		error;
	int		export;

	export = ((t_command *)ast->data)->args_len ? 1 : 0;
	iter = ast->assignements;
	while (iter)
	{
		ft_bzero(&shell->exp_lexer.buffer, sizeof(shell->exp_lexer.buffer));
		ft_bzero(&shell->exp_lexer.var, sizeof(shell->exp_lexer.var));
		error = 0;
		expanded = expand(shell, iter->var, &error);
		if (error || set_var_full(vars, expanded, export))
			return (1);
		if (shell->exp_lexer.buffer.buffer)
			free(shell->exp_lexer.buffer.buffer);
		iter = iter->next;
	}
	return (0);
}

static int	exec_cmd_internal(t_shell *shell, t_ast *ast)
{
	int		ret;

	if (ast->assignements)
	{
		if (!(shell->exec_vars = copy_vars(shell->vars, 0)))
			return (127);
		if (set_assignements(shell, ast, &shell->exec_vars))
			return (127);
		ret = exec(shell, ast);
		free_vars(&shell->exec_vars);
	}
	else
	{
		shell->exec_vars = shell->vars;
		ret = exec(shell, ast);
		shell->exec_vars = NULL;
	}
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
		return ((ast->ret = 127));
	ret = 0;
	if (((t_command *)ast->data)->args_len == 0)
	{
		if (set_assignements(shell, ast, &shell->vars))
			return (127);
	}
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
