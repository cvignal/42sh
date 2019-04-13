/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usub.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 06:24:13 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 06:50:40 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"

int	exec_ari_usub(t_shell *shell, t_ast *ast)

{
	int	value;

	ast->right->exec(shell, ast->right);
	if (ast->right->data)
	{
		value = ft_atoi(ast->right->data);
		free(ast->data);
		if (!(ast->data = ft_itoa(-value)))
			ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		ast->ret = !value;
	}
	return (!value);
}
