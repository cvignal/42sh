/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   div.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:42:03 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/09 04:13:54 by gchainet         ###   ########.fr       */
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

	(void)shell;
	if (!ast->left->data || !ast->right->data)
		return (1);
	a = ft_atoi(ast->left->data);
	b = ft_atoi(ast->right->data);
	free(ast->data);
	if (b == 0)
	{
		ft_dprintf(STDERR_FILENO, "%s: division by zero\n", EXEC_NAME);
		free(ast->data);
		ast->data = NULL;
		return (1);
	}
	res = a / b;
	ast->data = ft_itoa(a / b);
	ast->ret = !res;
	return (res);
}
