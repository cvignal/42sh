/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <gchainet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:14:15 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/22 14:22:06 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "jobs.h"
#include "ast.h"
#include "libft.h"
#include "fill_line.h"

static const t_readline	g_functions[2] =\
{
	{0, &fill_line},
	{1, &alt_fill_line}
};

static void				exec_ast(t_shell *shell, t_token *tokens)
{
	t_ast	*ast;
	int ret;

	ret = parse(shell, tokens);
	if (ret == PARSER_COMPLETE)
	{
		// set shell pgid

		// Create initial job
		// - Then create new ones when needed (; && ||) wow there
		// Set it to ast
		// exec creates procs and appends them to ast->job
		// replace ALL wait_loop by register_job

		ast = shell->parser.ret;
		if (!(ast->job = new_job()))
			exit(-1);
		ast->exec(shell, ast);
		close_everything(shell);
		ast->ret = register_job(shell, ast->job);
		shell->ret_cmd = ast->ret;
		ast->del(ast);
		shell->parser.ret = NULL;
	}
	add_to_history(shell->line.data, shell, 0);
	reset_terminal_mode(shell);
	raw_terminal_mode(shell);
	print_prompt(&shell->parser, shell, ret == PARSER_MORE_INPUT);
}

int						main(int ac, char **av, char **environ)
{
	t_shell		shell;
	t_token		*tokens;
	int			ret;

	(void)ac;
	(void)av;
	if (init_shell(&shell, environ))
		return (free_shell(&shell));
	ret = check_validity(&shell);
	print_prompt(&shell.parser, &shell, 0);
	disable_signal(&shell);
	while (!g_functions[ret].f(&shell))
	{
		if (!(tokens = lex(&shell)))
		{
			add_to_history(shell.line.data, &shell, 1);
			print_prompt(&shell.parser, &shell, 1);
		}
		else
			exec_ast(&shell, tokens);
		free_line(&shell.line);
		raw_terminal_mode(&shell);
	}
	builtin_exit(&shell, NULL);
}
