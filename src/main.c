/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:14:15 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/24 17:21:28 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "21sh.h"
#include "ast.h"
#include "libft.h"
#include "fill_line.h"

static void	exec_ast(t_shell *shell, t_token *tokens)
{
	t_ast	*ast;

	if ((ast = parse(shell, tokens)))
	{
		ast->exec(shell, ast);
		ast->del(ast);
	}
}

int			main(int ac, char **av, char **environ)
{
	t_shell		shell;
	t_token		*tokens;

	(void)ac;
	(void)av;
	if (init_shell(&shell, environ))
		return (1);
	ft_printf("%s ", PROMPT);
	shell.history = NULL;
	while (!fill_line(&shell))
	{
		tokens = lex(&shell, shell.line);
		if (!tokens)
			ft_printf("%s ", INCOMPLETE_INPUT_PROMPT);
		else
		{
			exec_ast(&shell, tokens);
			ft_printf("%s ", PROMPT);
			free(shell.line);
			shell.line = NULL;
		}
	}
	free_shell(&shell);
	return (0);
}
