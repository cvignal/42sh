/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:51:04 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 14:24:23 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

static int	exec_ari_eq_var(t_shell *shell, t_ast *ast)
{
	ast->right->exec(shell, ast->right);
	if (!ast->right->data)
		return (exec_ari_fail(ast));
	free(ast->data);
	if (ast->right->data)
	{
		ast->ret = !ft_atoi(ast->right->data);
		if (set_var(&shell->vars, ast->left->data, ast->right->data, 0))
			ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		if (!(ast->data = ft_strdup(ast->right->data)))
			ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		return (ast->ret);
	}
	ast->ret = 1;
	ast->data = NULL;
	return (1);
}

static int	exec_ari_eq_non_var(t_ast *ast)
{
	ft_dprintf(STDERR_FILENO, "%s: attempt assignement to non-variable\n",
			EXEC_NAME);
	ast->ret = 1;
	free(ast->data);
	ast->data = NULL;
	return (1);
}

int			exec_ari_eq(t_shell *shell, t_ast *ast)
{
	if (!ast->left->data)
		return (exec_ari_fail(ast));
	if (arithmetic_is_var(ast->left->data))
		return (exec_ari_eq_var(shell, ast));
	else
		return (exec_ari_eq_non_var(ast));
}
