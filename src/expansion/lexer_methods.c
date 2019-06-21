/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 20:59:58 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/06 08:44:48 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "libft.h"

int	exp_lexer_add_to_buff(t_shell *shell, char c, int mask)
{
	(void)mask;
	if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_pop_add_to_buff(t_shell *shell, char c, int mask)
{
	char	*tmp;

	(void)mask;
	if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	tmp = exp_ss_pop(&shell->exp_lexer);
	if (add_string_to_exp_buff(&shell->exp_lexer, tmp))
	{
		free(tmp);
		return (EXP_LEXER_RET_ERROR);
	}
	free(tmp);
	return (EXP_LEXER_RET_CONT);
}

int	exp_lexer_add_to_var(t_shell *shell, char c, int mask)
{
	(void) mask;
	if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}
static int set_var_value(t_shell  *shell, char *name)
{
	const char	*value;

	if (ft_strlen(name) == 1 && is_special_param(name[0]))
	{
		if (expand_special_params(shell, name[0]))
				return (1);
	}
	else if ((value = get_var_value(get_var(shell->vars , name))))
	{
		if (add_string_to_exp_buff(&shell->exp_lexer, value))
		{
			free(name);
			return (1);
		}
	}
	free(name);
	return (0);
}

int	exp_lexer_cut_var(t_shell *shell, char c, int mask)
{
	char		*name;
	int		ret;

	(void)c;
	ret = shell->exp_lexer.state->state == EXP_STATE_VAR ? 0 : EXP_LEXER_RET_CONT;
	name = exp_ss_pop(&shell->exp_lexer);
	if (shell->exp_lexer.state->state == EXP_STATE_WORD
			&& (mask & EXP_LEXER_MASK_FIELD_SPLITTING))
		shell->exp_lexer.split = 1;
	if (name)
		if (set_var_value(shell, name))
			return (EXP_LEXER_RET_CONT);
	if (shell->exp_lexer.state->state == EXP_STATE_WORD)
		shell->exp_lexer.split = 0;
	return (ret);
}

int	exp_lexer_push_var(t_shell *shell, char c, int mask)
{
	if (!(mask & EXP_LEXER_MASK_VARIABLE))
		return (exp_lexer_add_to_buff(shell, c, mask));
	if (mask & EXP_LEXER_MASK_FIELD_SPLITTING)
		shell->exp_lexer.split = 1;
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_VAR))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}
