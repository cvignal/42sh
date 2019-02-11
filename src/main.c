/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:14:15 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/11 18:40:34 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "ast.h"
#include "libft.h"
#include "fill_line.h"

static void	print_prompt(const char *def, t_parser *parser, t_shell *shell)
{
	if (parser->pss->state != PS_NONE)
		ft_dprintf(shell->fd_op, "%s ", INCOMPLETE_INPUT_PROMPT);
	else
		ft_dprintf(shell->fd_op, "%s ", def);
}

static void	exec_ast(t_shell *shell, t_token *tokens)
{
	t_ast	*ast;

	if (parse(shell, tokens) == PARSER_COMPLETE)
	{
		ast = shell->parser.ret;
		ast->exec(shell, ast);
		close_everything(shell);
		wait_loop(ast);
		ast->del(ast);
		add_to_history(shell->line.data, shell, 0);
	}
	print_prompt(PROMPT, &shell->parser, shell);
}

int			main(int ac, char **av, char **environ)
{
	t_shell		shell;
	t_token		*tokens;

	(void)ac;
	(void)av;
	if (init_shell(&shell, environ))
		return (1);
	print_prompt(PROMPT, &shell.parser, &shell);
	while (!fill_line(&shell))
	{
		disable_signal();
		if (!(tokens = lex(&shell)))
		{
			add_to_history(shell.line.data, &shell, 1);
			print_prompt(INCOMPLETE_INPUT_PROMPT, &shell.parser, &shell);
		}
		else
			exec_ast(&shell, tokens);
		raw_terminal_mode(&shell);
		free_line(&shell.line);
	}
	free_shell(&shell);
	return (0);
}
