/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:53:07 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/01 14:35:50 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

static char	*exec_complete_ari(t_shell *shell)
{
	char	*ret;
	t_ast	*ast;

	ast = shell->parser.ret;
	if (ast->rec_lvl > 10)
	{
		ast->del(ast);
		ft_dprintf(STDERR_FILENO, "%s: arithmetic recursion level too high\n",
				EXEC_NAME);
		return (NULL);
	}
	ast->exec(shell, ast);
	if (ast->data)
		ret = ft_strdup(ast->data);
	else
		ret = NULL;
	ast->del(ast);
	return (ret);
}

static void	set_rec_lvl(t_ast *ast, int rec_lvl)
{
	if (ast)
	{
		ast->rec_lvl = rec_lvl;
		set_rec_lvl(ast->left, rec_lvl);
		set_rec_lvl(ast->right, rec_lvl);
	}
}

static char	*get_ari_value(t_shell *shell, const char *input, int rec_lvl)
{
	t_token	*tokens;

	if (lss_push(&shell->lexer, LSTATE_ARI_NONE))
		return (NULL);
	if (!(tokens = lex(shell, input)))
		return (NULL);
	set_unary(tokens);
	lss_pop(&shell->lexer);
	shell->parser.ret = NULL;
	if (pss_push(&shell->parser, PS_ARI))
		return (NULL);
	if (parse(shell, tokens) == PARSER_COMPLETE)
	{
		set_rec_lvl(shell->parser.ret, rec_lvl + 1);
		return (exec_complete_ari(shell));
	}
	return (NULL);
}

int	exec_ari_value(t_shell *shell, t_ast *ast)
{
	const char	*var;
	char		*value;
	int			ret;

	ret = 0;
	if (arithmetic_is_var(ast->data))
	{
		if ((var = get_var_value(get_var(shell->vars, ast->data))))
		{
			if (!(value = get_ari_value(shell, var, ast->rec_lvl)))
				return (exec_ari_fail(ast));
			ret = ft_atoi(value);
			free(value);
		}
	}
	else
		ret = ft_atoi(ast->data);
	free(ast->data);
	if (!(ast->data = ft_itoa(ret)))
		ft_dprintf(STDERR_FILENO, "%s: %s\n" EXEC_NAME, MEMORY_ERROR_MSG);
	ast->ret = !ret;
	return (ret);
}
