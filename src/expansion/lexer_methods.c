/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:59:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/12 21:35:41 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "libft.h"

int	exp_lexer_add_to_buff(t_shell *shell, char c, int mask)
{
	(void)mask;
	if (add_to_exp_buff(&shell->exp_lexer.buffer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_add_to_var(t_shell *shell, char c, int mask)
{
	(void)mask;
	if (add_to_exp_buff(&shell->exp_lexer.var, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_cut_var(t_shell *shell, char c, int mask)
{
	char	*value;
	int		i;

	(void)c;
	(void)mask;
	if (shell->exp_lexer.var.pos)
	{
		value = get_env_value(shell, shell->exp_lexer.var.buffer);
		if (value)
		{
			i = 0;
			while (value[i])
			{
				if (add_to_exp_buff(&shell->exp_lexer.buffer, value[i]))
					return (EXP_LEXER_RET_ERROR);
				++i;
			}
		}
		free(shell->exp_lexer.var.buffer);
		ft_bzero(&shell->exp_lexer.var, sizeof(shell->exp_lexer.var));
	}
	exp_ss_pop(&shell->exp_lexer);
	return (0);
}

int	exp_lexer_push_var(t_shell *shell, char c, int mask)
{
	(void)c;
	if (!(mask & EXP_LEXER_MASK_VARIABLE))
		return (exp_lexer_add_to_buff(shell, c, mask));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_VAR))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}
