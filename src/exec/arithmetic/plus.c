/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:37:53 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 14:28:01 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int	exec_ari_plus(t_shell *shell, t_ast *ast)
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
	res = a + b;
	free(ast->data);
	ast->data = ft_itoa(res);
	ast->ret = !res;
	return (res);
}
