/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:42:03 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 14:22:43 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int	exec_ari_div(t_shell *shell, t_ast *ast)
{
	int	a;
	int	b;
	int	res;

	ast->left->exec(shell, ast->left);
	if (!ast->left->data)
		return (exec_ari_fail(ast));
	ast->right->exec(shell, ast->right);
	if (!ast->right->data)
		return (exec_ari_fail(ast));
	a = ft_atoi(ast->left->data);
	b = ft_atoi(ast->right->data);
	if (!b)
	{
		ft_dprintf(STDERR_FILENO, "%s: division by zero\n", EXEC_NAME);
		return (exec_ari_fail(ast));
	}
	res = a / b;
	ast->ret = !res;
	free(ast->data);
	ast->data = ft_itoa(a / b);
	return (ast->ret);
}
