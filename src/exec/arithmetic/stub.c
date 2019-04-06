/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stub.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 00:37:19 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/07 00:41:24 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int		stub_exec_ari(t_shell *shell, t_ast *ast)
{
	(void)shell;
	(void)ast;
	ft_printf("fixme: arithmetic execution stub\n");
	return (0);
}

void	stub_del_ari(t_ast *ast)
{
	(void)ast;
	ft_printf("fixme: arithmetic delete stub\n");
}
