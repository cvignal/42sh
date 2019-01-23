/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:14:15 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/23 12:14:38 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"
#include "libft.h"
#include "fill_line.h"

static void	exec_ast(t_shell *shell, t_token *tokens)
{
	t_ast	*ast;

	if (parse(shell, tokens) == PARSER_COMPLETE)
	{
		ast = shell->parser.ret;
		ast->exec(shell, ast);
		wait_loop(ast);
		ast->del(ast);
	}
}

static void	print_prompt(const char *def, t_parser *parser)
{
	if (parser->pss->state != PS_NONE)
		ft_printf("%s ", INCOMPLETE_INPUT_PROMPT);
	else
		ft_printf("%s ", def);
}

int			main(int ac, char **av, char **environ)
{
	t_shell		shell;
	t_token		*tokens;

	(void)ac;
	(void)av;
	if (init_shell(&shell, environ))
		return (1);
	print_prompt(PROMPT, &shell.parser);
	shell.history = NULL;
	disable_signal();
	load_history(&shell);
	while (!fill_line(&shell))
	{
		tokens = lex(&shell);
		disable_signal();
		if (!tokens)
		{
			add_to_history(shell.line.data, &shell, 1);
			print_prompt(INCOMPLETE_INPUT_PROMPT, &shell.parser);
		}
		else
		{
			exec_ast(&shell, tokens);
			print_prompt(PROMPT, &shell.parser);
			add_to_history(shell.line.data, &shell, 0);
		}
		free_line(&shell.line);
	}
	free_shell(&shell);
	return (0);
}
