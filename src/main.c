/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <gchainet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:14:15 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/25 13:41:42 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "shell.h"
#include "jobs.h"
#include "ast.h"
#include "libft.h"
#include "fill_line.h"

static const t_readline	g_functions[3] =\
{
	{0, &fill_line},
	{1, &alt_fill_line},
	{2, &read_from_file} 
};

static void				exec_ast(t_shell *shell, t_token *tokens)
{
	t_ast	*ast;

	parse(shell, tokens);
	if (shell->parser.ret_status == PARSER_COMPLETE)
	{
		reset_terminal_mode();
		ast = shell->parser.ret;
		exec_job(shell, ast, NULL);
		close_everything(shell);
		ast->del(ast);
		shell->parser.ret = NULL;
	}
	else if (shell->parser.ret_status == PARSER_ERROR)
		set_ret(shell, NULL, 2);
	add_to_history(shell->line.data, shell, 0);
}

int						main(int ac, char **av, const char **environ)
{
	t_shell		shell;
	t_token		*tokens;
	int			ret;

	if (init_shell(&shell, environ))
		return (free_shell(&shell));
	parse_args(&shell, ac, av);
	ret = check_validity(&shell);
	set_special_var(&shell.vars, SPECIAL_VAR_RET, "0");
	print_prompt(&shell, 0);
	disable_signal(&shell);
	while (!g_functions[ret].f(&shell))
	{
		if (!(tokens = lex(&shell, shell.line.data)))
			add_to_history(shell.line.data, &shell, 1);
		else
			exec_ast(&shell, tokens);
		free_line(&shell.line);
		raw_terminal_mode(&shell);
		print_prompt(&shell, tokens ? 0 : 1);
	}
	builtin_exit(&shell, NULL);
}
