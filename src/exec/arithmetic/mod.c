/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:43:37 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 08:24:45 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int	exec_ari_mod(t_shell *shell, t_ast *ast)
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
	if (!b)
	{
		ft_dprintf(STDERR_FILENO, "%s: division by zero\n", EXEC_NAME);
		ast->data = NULL;
		return (1);
	}
	res = a % b;
	ast->ret = !res;
	ast->data = ft_itoa(res);
	return (ast->ret);
}
