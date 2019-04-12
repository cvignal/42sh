/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:42:03 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/12 22:29:03 by gchainet         ###   ########.fr       */
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

	a = ast->left->exec(shell, ast->left);
	b = ast->right->exec(shell, ast->right);
	free(ast->data);
	if (!ast->left->data || !ast->right->data)
	{
		ast->data = NULL;
		return (1);
	}
	if (!b)
	{
		ft_dprintf(STDERR_FILENO, "%s: division by zero\n", EXEC_NAME);
		ast->data = NULL;
		return (1);
	}
	res = a / b;
	ast->ret = !res;
	ast->data = ft_itoa(a / b);
	return (res);
}
