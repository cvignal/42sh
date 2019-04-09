/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:51:04 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/09 04:59:26 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

static int	exec_ari_eq_var(t_shell *shell, t_ast *ast)
{
	int		ret;
	char	*new_value;

	ret = ast->right->exec(shell, ast);
	if (ast->right->data)
	{
		if (!(new_value = ft_itoa(ret))
				|| add_shell_var(shell, ast->left->data, new_value))
		{
			ft_dprintf(STDERR_FILENO,
					"%s: unable to allocate memory for variable assignement\n",
					EXEC_NAME);
			ast->ret = 1;
			return (1);
		}
		ast->ret = !ret;
		return (ret);
	}
	ast->ret = 1;
	free(ast->data);
	ast->data = NULL;
	return (1);
}

static int	exec_ari_eq_non_var(t_ast *ast)
{
	ft_dprintf(STDERR_FILENO, "%s: attempt assignement to non-variable\n",
			EXEC_NAME);
	ast->ret = 1;
	free(ast->data);
	ast->data = NULL;
	return (1);
}

int	exec_ari_eq(t_shell *shell, t_ast *ast)
{
	if (arithmetic_is_var(ast->left->data))
		return (exec_ari_eq_var(shell, ast));
	else
		return (exec_ari_eq_non_var(ast));
}
