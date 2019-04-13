/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 23:58:18 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 04:10:16 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"

int		exec_ari_statement(t_shell *shell, t_ast *ast)
{
	t_token	*tokens;
	char	*expanded;
	int		error;

	if (lss_push(&shell->lexer, LSTATE_ARI_NONE))
		return (1);
	error = 0;
	expanded = expand(shell, ast->data, &error);
	if (error || !expanded || !(tokens = lex(shell, expanded)))
		return (1);
	free(expanded);
	lss_pop(&shell->lexer);
	shell->parser.ret = NULL;
	if (pss_push(&shell->parser, PS_ARI))
		return (1);
	if (parse(shell, tokens) == PARSER_COMPLETE)
	{
		shell->parser.ret->exec(shell, shell->parser.ret);
		ast->ret = shell->parser.ret->ret;
		shell->parser.ret->del(shell->parser.ret);
	}
	return (0);
}

void	free_ari_statement(t_ast *ast)
{
	free(ast->data);
	free(ast);
}
