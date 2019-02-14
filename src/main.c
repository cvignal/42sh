/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:14:15 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/14 14:50:54 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "ast.h"
#include "libft.h"
#include "fill_line.h"

void		print_prompt(t_parser *parser, t_shell *shell, int flag)
{
	char	*cwd;
	char	*str;

	cwd = getcwd(NULL, MAX_PATH);
	if ((parser && parser->pss->state != PS_NONE) || flag)
	{
		shell->prompt_len = 2;
		ft_dprintf(shell->fd_op, "%s ", INCOMPLETE_INPUT_PROMPT);
	}
	else
	{
		if (ft_strrchr(cwd, '/') && ft_strchr(cwd, '/') != ft_strrchr(cwd, '/'))
			str = ft_strrchr(cwd, '/') + 1;
		else
			str = cwd;
		shell->prompt_len = ft_strlen(str) + 7;
		ft_dprintf(shell->fd_op, "%s%s%s %s[ %s ]%s ", YELLOW, "\xE2\x86\xAA"
				, EOC, GREEN, str, EOC);
	}
	free(cwd);
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
		shell->parser.ret = NULL;
	}
	add_to_history(shell->line.data, shell, 0);
	print_prompt(&shell->parser, shell, 0);
}

int			main(int ac, char **av, char **environ)
{
	t_shell		shell;
	t_token		*tokens;

	(void)ac;
	(void)av;
	if (init_shell(&shell, environ))
		return (1);
	print_prompt(&shell.parser, &shell, 0);
	while (!fill_line(&shell))
	{
		disable_signal();
		if (!(tokens = lex(&shell)))
		{
			add_to_history(shell.line.data, &shell, 1);
			print_prompt(&shell.parser, &shell, 1);
		}
		else
			exec_ast(&shell, tokens);
		raw_terminal_mode(&shell);
		free_line(&shell.line);
	}
	free_shell(&shell);
	return (0);
}
