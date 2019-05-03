/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_sup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 23:06:52 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 14:21:21 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int	exec_ari_cmp_sup(t_shell *shell, struct s_ast *ast)
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
	free(ast->data);
	a = ft_atoi(ast->left->data);
	b = ft_atoi(ast->right->data);
	res = a > b;
	ast->data = ft_itoa(res);
	ast->ret = !res;
	return (res);
}
