/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:14:15 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/19 18:31:36 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "minishell.h"
#include "ast.h"
#include "libft.h"
#include "fill_line.h"

int			main(int ac, char **av, char **environ)
{
	t_ast		*ast;
	t_shell		shell;

	(void)ac;
	(void)av;
	if (init_shell(&shell, environ))
		return (1);
	ft_printf("$> ");
	while ((shell.line = fill_line()))
	{
		if ((ast = parse(&shell, lex(&shell, shell.line))))
		{
			ast->exec(&shell, ast);
			ast->del(ast);
		}
		free(shell.line);
		ft_printf("$> ");
	}
	free_shell(&shell);
	return (0);
}
