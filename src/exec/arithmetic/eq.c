/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:51:04 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/07 03:01:33 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

int	exec_ari_eq(t_shell *shell, t_ast *ast)
{
	(void)shell;
	(void)ast;
	ft_dprintf(STDERR_FILENO, "%s: stub: arithmetic assignation\n", EXEC_NAME);
	return (0);
}
