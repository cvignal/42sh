/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:43:54 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/20 11:54:29 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "ast.h"

int		exec_cmd(t_shell *shell, t_ast *ast)
{
	(void)shell;
	(void)ast;
	return (0);
}

void	free_cmd(t_ast *ast)
{
	free_command(ast->data);
	free(ast);
}
