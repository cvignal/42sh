/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:43:54 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/12 21:10:53 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"

static void	debug(t_command *command)
{
	unsigned int	len;
	unsigned int	i;

	i = 0;
	len = 0;
	while (command->args[len])
		++len;
	ft_printf("len args: %u\n", len);
	while (i < len)
		ft_printf("%s\n", command->args[i++]);
	len = 0;
	i = 0;
	while (command->args_value[len])
		++len;
	ft_printf("len value: %u\n", len);
	while (i < len)
		ft_printf("%s\n", command->args_value[i++]);
}

int		exec_cmd(t_shell *shell, t_ast *ast)
{
	int	ret;

	if (prepare_redirs(shell, ast, ast))
	{
		ast->ret = 127;
		return (1);
	}
	ret = exec(shell, ast);
	debug(ast->data);
	reset_redirs(shell, ast);
	return (ret);
}

void	free_cmd(t_ast *ast)
{
	free_command(ast->data);
	free_ast(ast);
}
