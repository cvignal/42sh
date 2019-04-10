/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:59:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/10 03:55:49 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "libft.h"

int	exp_lexer_add_to_buff(t_shell *shell, t_exp_lexer *lexer, char c)
{
	(void)shell;
	if (add_to_exp_buff(&lexer->buffer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_add_to_var(t_shell *shell, t_exp_lexer *lexer, char c)
{
	(void)shell;
	if (add_to_exp_buff(&lexer->var, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_cut_var(t_shell *shell, t_exp_lexer *lexer, char c)
{
	t_var	*value;
	int		i;

	(void)c;
	if (lexer->var.pos)
	{
		value = get_var(shell->vars, lexer->var.buffer);
		if (value)
		{
			i = 0;
			while (value->var[i])
			{
				if (add_to_exp_buff(&lexer->buffer, value->var[i]))
					return (EXP_LEXER_RET_ERROR);
				++i;
			}
		}
		free(lexer->var.buffer);
		ft_bzero(&lexer->var, sizeof(lexer->var));
	}
	exp_ss_pop(lexer);
	return (0);
}

int	exp_lexer_push_var(t_shell *shell, t_exp_lexer *lexer, char c)
{
	(void)shell;
	(void)c;
	if (exp_ss_push(lexer, EXP_STATE_VAR))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}
