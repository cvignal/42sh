/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 02:59:42 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 14:36:15 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"

int	exec_ari_and(t_shell *shell, struct s_ast *ast)
{
	ast->left->exec(shell, ast->left);
	if (!ast->left->data)
		return (exec_ari_fail(ast));
	if (!ft_atoi(ast->left->data))
	{
		ast->right->exec(shell, ast->right);
		if (!ast->right->data)
			return (exec_ari_fail(ast));
		ast->ret = !!ft_atoi(ast->right->data);
	}
	else
		ast->ret = 1;
	free(ast->data);
	ast->data = ft_itoa(ast->ret);
	return (0);
}
