/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:53:07 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 02:41:51 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int	exec_ari_value(t_shell *shell, t_ast *ast)
{
	t_var	*var;
	int		ret;

	ast->ret = 0;
	if (arithmetic_is_var(ast->data))
	{
		var = get_var(shell->vars, ast->data);
		if (var)
			ret = ft_atoi(var->var);
		else
			ret = 0;
	}
	else
		ret = ft_atoi(ast->data);
	free(ast->data);
	if (!(ast->data = ft_itoa(ret)))
	{
		ft_dprintf(STDERR_FILENO,
				"%s: unable to allocate memory for variable assignement\n",
				EXEC_NAME);
	}
	ast->ret = !ret;
	return (ret);
}
