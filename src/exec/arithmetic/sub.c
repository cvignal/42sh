/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:40:33 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/12 22:31:43 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int	exec_ari_sub(t_shell *shell, t_ast *ast)
{
	int	a;
	int	b;
	int	res;

	a = ast->left->exec(shell, ast->left);
	b = ast->right->exec(shell, ast->right);
	free(ast->data);
	if (!ast->left->data || !ast->right->data)
	{
		ast->data = NULL;
		return (1);
	}
	res = a - b;
	ast->data = ft_itoa(res);
	ast->ret = !res;
	return (res);
}
