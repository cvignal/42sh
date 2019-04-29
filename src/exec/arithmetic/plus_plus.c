/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plus_plus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 04:28:07 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/26 01:24:48 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int	exec_ari_pre_plus_plus(t_shell *shell, t_ast *ast)
{
	int		value;
	t_var	*var;
	char	*res;

	free(ast->data);
	if ((var = get_var(shell->vars, ast->right->data)))
		value = ft_atoi(get_var_value(var));
	else
		value = 0;
	ast->data = ft_itoa(++value);
	ast->ret = !value;
	if (!ast->data)
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
	res = ft_itoa(value);
	if (!res)
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
	set_var(&shell->vars, ast->right->data, res, var ? var->exported : 0);
	free(res);
	return (!value);
}

int	exec_ari_post_plus_plus(t_shell *shell, t_ast *ast)
{
	int		value;
	t_var	*var;
	char	*res;

	free(ast->data);
	if ((var = get_var(shell->vars, ast->right->data)))
		value = ft_atoi(get_var_value(var));
	else
		value = 0;
	ast->ret = !value;
	ast->data = ft_itoa(value++);
	if (!ast->data)
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
	res = ft_itoa(value);
	if (!res)
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
	set_var(&shell->vars, ast->right->data, res, var ? var->exported : 0);
	free(res);
	return (!value);
}
