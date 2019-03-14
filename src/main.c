/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:14:15 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/14 13:59:25 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "ast.h"
#include "libft.h"
#include "fill_line.h"

static const t_readline	g_functions[2] =\
{
	{0, &fill_line},
	{1, &alt_fill_line}
};

void					print_prompt(t_parser *parser, t_shell *shell, int flag)
{
	char	*cwd;
	char	*str;

	if (check_validity(shell))
		return ;
	raw_terminal_mode(shell);
	cwd = getcwd(NULL, MAX_PATH);
	if ((parser && parser->pss->state != PS_NONE) || flag
			|| shell->ret_cmd == -1)
	{
		shell->prompt_len = 2;
		ft_dprintf(shell->fd_op, "%s ", INCOMPLETE_INPUT_PROMPT);
		shell->ret_cmd = -1;
	}
	else
	{
		if (ft_strrchr(cwd, '/') && ft_strchr(cwd, '/') != ft_strrchr(cwd, '/'))
			str = ft_strrchr(cwd, '/') + 1;
		else
			str = cwd;
		shell->prompt_len = ft_strlen(str) + 7;
		ft_dprintf(shell->fd_op, "%s%s%s %s[ %s ]%s ", YELLOW, "\xE2\x86\xAA"
				, EOC, !shell->ret_cmd ? GREEN : RED, str, EOC);
	}
	free(cwd);
}

static void				exec_ast(t_shell *shell, t_token *tokens)
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
	add_to_history(shell->line.data, shell, 0);
	reset_terminal_mode(shell);
	raw_terminal_mode(shell);
	print_prompt(&shell->parser, shell, 0);
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
	while (!g_functions[ret].f(&shell))
	{
		disable_signal();
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
	free_shell(&shell);
	return (0);
}
