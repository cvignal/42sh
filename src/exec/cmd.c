/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:43:54 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/06 08:03:32 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"

int		exec_cmd(t_shell *shell, t_ast *ast)
{
	return (exec(shell, ast));
}

void	free_cmd(t_ast *ast)
{
	free_command(ast->data);
	free_ast(ast);
}
