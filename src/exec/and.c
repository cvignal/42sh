/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 21:40:25 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/03 00:19:47 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"

int		exec_and(t_shell *shell, t_ast *ast)
{
	if (shell->ctrlc)
		return (0);
	if (exec_job(shell, ast->left, NULL))
		return (-1);
	if (ast->left->ret == 0)
	{
		if (exec_job(shell, ast->right, ast->job))
			return (-1);
		ast->ret = ast->right->ret;
	}
	else
		ast->ret = ast->left->ret;
	return (0);
}
