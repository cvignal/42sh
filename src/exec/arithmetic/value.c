/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 01:53:07 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/30 02:53:33 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "arithmetic.h"
#include "libft.h"

static char	*exec_complete_ari(t_shell *shell)
{
	char	*ret;

	shell->parser.ret->exec(shell, shell->parser.ret);
	ret = ft_strdup(shell->parser.ret->data);
	shell->parser.ret->del(shell->parser.ret);
	return (ret);
}

static char	*get_ari_value(t_shell *shell, const char *input)
{
	t_token	*tokens;
	int		error;

	if (lss_push(&shell->lexer, LSTATE_ARI_NONE))
		return (NULL);
	error = 0;
	if (error || !(tokens = lex(shell, input)))
		return (NULL);
	set_unary(tokens);
	lss_pop(&shell->lexer);
	shell->parser.ret = NULL;
	if (pss_push(&shell->parser, PS_ARI))
		return (NULL);
	if (parse(shell, tokens) == PARSER_COMPLETE)
		return (exec_complete_ari(shell));
	return (NULL);
}

int	exec_ari_value(t_shell *shell, t_ast *ast)
{
	const char	*var;
	char		*value;
	int			ret;

	ast->ret = 0;
	if (arithmetic_is_var(ast->data))
	{
		if ((var = get_var_value(get_var(shell->vars, ast->data)))
				&& (value = get_ari_value(shell, var)))
		{
			ret = ft_atoi(value);
			free(value);
		}
		else
			ret = 0;
	}
	else
		ret = ft_atoi(ast->data);
	free(ast->data);
	if (!(ast->data = ft_itoa(ret)))
	{
		ft_dprintf(STDERR_FILENO,
				"%s: unable to allocate memory for variable assignement\n",
				EXEC_NAME);
	}
	ast->ret = !ret;
	return (ret);
}
