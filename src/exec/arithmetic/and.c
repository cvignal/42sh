/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 02:59:42 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/28 03:06:59 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"

int	exec_ari_and(t_shell *shell, struct s_ast *ast)
{
	ast->left->exec(shell, ast->left);
	if (ast->left->data && !ast->left->ret)
	{
		ast->right->exec(shell, ast->right);
		ast->ret = !!ast->right->ret;
	}
	else
		ast->ret = 1;
	free(ast->data);
	ast->data = ft_itoa(ast->ret);
	return (0);
}
