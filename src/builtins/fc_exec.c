/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:23:36 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/14 13:51:50 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

void	fc_exec_ast(t_shell *shell, t_token *tokens)
{
	t_ast	*ast;

	if (parse(shell, tokens) == PARSER_COMPLETE)
	{
		ast = shell->parser.ret;
		ast->exec(shell, ast);
		close_everything(shell);
		wait_loop(ast);
		shell->ret_cmd = ast->ret;
		ast->del(ast);
		shell->parser.ret = NULL;
	}
	reset_terminal_mode(shell);
	raw_terminal_mode(shell);
}

int		fc_init_shell(t_shell *shell, char **environ)
{
	ft_bzero(shell, sizeof(*shell));
	if (init_lexer(&shell->lexer) || init_parser(&shell->parser)
			|| init_exp_lexer(&shell->exp_lexer))
		return (1);
	shell->hash_table = malloc(sizeof(*shell->hash_table) * HASH_TABLE_SIZE);
	if (!shell->hash_table)
		return (1);
	shell->used_fd = NULL;
	ft_bzero(shell->hash_table, sizeof(*shell->hash_table) * HASH_TABLE_SIZE);
	ft_bzero(&shell->line, sizeof(shell->line));
	if (!(shell->env = copy_env(environ)))
	{
		ft_dprintf(2, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		return (1);
	}
	return (0);
}

int		fc_exec_line(char *str, t_shell *shell)
{
	t_shell tmp_shell;
	t_token	*tokens;

	fc_init_shell(&tmp_shell, shell->env);
	ft_addchar(&tmp_shell, str, 1);
	ft_printf("\n");
	tokens = lex(&tmp_shell);
	fc_exec_ast(&tmp_shell, tokens);
	free_line(&tmp_shell.line);
	free_shell(&tmp_shell);
	return (0);
}
