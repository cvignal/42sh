/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 23:58:18 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 14:39:31 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "arithmetic.h"

static void	exec_complete_ari(t_shell *shell, t_ast *ast)
{
	shell->parser.ret->exec(shell, shell->parser.ret);
	ast->ret = shell->parser.ret->ret;
	set_ret(shell, ast, ast->ret);
	shell->parser.ret->del(shell->parser.ret);
}

int			exec_ari_statement(t_shell *shell, t_ast *ast)
{
	t_token	*tokens;
	char	*expanded;
	int		error;

	if (lss_push(&shell->lexer, LSTATE_ARI_NONE))
		return (1);
	error = 0;
	if (!(expanded = expand_no_split(shell, ast->data, &error,
					EXP_LEXER_MASK_ALL)))
		return (0);
	if (error || !(tokens = lex(shell, expanded)))
	{
		free(expanded);
		return (1);
	}
	set_unary(tokens);
	free(expanded);
	lss_pop(&shell->lexer);
	shell->parser.ret = NULL;
	if (pss_push(&shell->parser, PS_ARI))
		return (1);
	if (parse(shell, tokens) == PARSER_COMPLETE)
		exec_complete_ari(shell, ast);
	else
		return (1);
	return (0);
}

void		free_ari_statement(t_ast *ast)
{
	free(ast->data);
	free(ast);
}
