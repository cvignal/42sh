/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_sup_eq.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 23:09:18 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/27 18:10:31 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int	exec_ari_cmp_sup_eq(t_shell *shell, struct s_ast *ast)
{
	int	a;
	int	b;
	int	res;

	ast->left->exec(shell, ast->left);
	ast->right->exec(shell, ast->right);
	free(ast->data);
	if (!ast->left->data || !ast->right->data)
	{
		ast->data = NULL;
		return (1);
	}
	a = ft_atoi(ast->left->data);
	b = ft_atoi(ast->right->data);
	res = a > b;
	ast->data = ft_itoa(res);
	ast->ret = !res;
	return (res);
}
