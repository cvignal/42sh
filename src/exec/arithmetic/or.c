/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/28 03:02:32 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/28 04:49:29 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"

int	exec_ari_or(t_shell *shell, struct s_ast *ast)
{
	ast->left->exec(shell, ast->left);
	if (ast->left->data && ft_atoi(ast->left->data))
	{
		ast->right->exec(shell, ast->right);
		ast->ret = !!ft_atoi(ast->right->data);
	}
	else
		ast->ret = 1;
	free(ast->data);
	ast->data = ft_itoa(ast->ret);
	return (0);
}
