/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:26:10 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/05 23:22:00 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

static void	set_exp_lexer_var_methods(t_exp_lexer *lexer)
{
	int	i;

	i = 0;
	while (i <= CHAR_MAX)
	{
		if (i != '}')
			lexer->methods[EXP_STATE_CURLY_EXP][i] = &exp_lexer_add_to_buff;
		lexer->methods[EXP_STATE_SPECIAL_PARAM][i] = &exp_lexer_cut_special_param;
		if (ft_isalnum(i) || i == '_')
			lexer->methods[EXP_STATE_VAR][i] = &exp_lexer_add_to_buff;
		else
			lexer->methods[EXP_STATE_VAR][i] = &exp_lexer_cut_var;
		++i;
	}
}

static void	set_exp_lexer_other(t_exp_lexer *lexer)
{
	lexer->methods[EXP_STATE_WORD]['\\'] = &exp_lexer_push_escaped;
	lexer->methods[EXP_STATE_WORD]['\\'] = &exp_lexer_push_escaped;
	lexer->methods[EXP_STATE_DQUOTE]['\\'] = &exp_lexer_push_escaped;
	lexer->methods[EXP_STATE_WORD]['\''] = &exp_lexer_push_squote;
	lexer->methods[EXP_STATE_WORD]['"'] = &exp_lexer_push_dquote;
	lexer->methods[EXP_STATE_WORD]['$'] = &exp_lexer_push_dollar;
	lexer->methods[EXP_STATE_DQUOTE]['$'] = &exp_lexer_push_dollar;
	lexer->methods[EXP_STATE_ARI_PAREN]['$'] = &exp_lexer_push_dollar;
	lexer->methods[EXP_STATE_DQUOTE]['"'] = &exp_lexer_pop_quote;
	lexer->methods[EXP_STATE_SQUOTE]['\''] = &exp_lexer_pop_quote;
	lexer->methods[EXP_STATE_ESCAPED]['\n'] = &exp_lexer_pop_quote;
	lexer->methods[EXP_STATE_WORD][0] = &exp_lexer_over;
	lexer->methods[EXP_STATE_SQUOTE][0] = &exp_lexer_error;
	lexer->methods[EXP_STATE_DQUOTE][0] = &exp_lexer_error;
	lexer->methods[EXP_STATE_DOLLAR][0] = &exp_lexer_dollar_fail;
	lexer->methods[EXP_STATE_VAR][0] = &exp_lexer_cut_var;
	lexer->methods[EXP_STATE_ARI][0] = &exp_lexer_pop_ari;
	lexer->methods[EXP_STATE_ARI_PAREN][0] = &exp_lexer_error;
	lexer->methods[EXP_STATE_ESCAPED][0] = &exp_lexer_error;
	lexer->methods[EXP_STATE_TILDE][0] = &exp_lexer_pop_tilde;
	lexer->methods[EXP_STATE_PROC_SUB][0] = &exp_lexer_error;
	lexer->methods[EXP_STATE_WORD]['~'] = &exp_lexer_push_tilde;
	lexer->methods[EXP_STATE_TILDE][':'] = &exp_lexer_pop_tilde;
	lexer->methods[EXP_STATE_TILDE]['/'] = &exp_lexer_pop_tilde;
	lexer->methods[EXP_STATE_PROC_SUB][')'] = &exp_lexer_pop_proc_sub;
}

static void	set_exp_lexer_dollar(t_exp_lexer *lexer)
{
	int	i;

	i = 0;
	while (i <= CHAR_MAX)
	{
		if (is_special_param(i))
			lexer->methods[EXP_STATE_DOLLAR][i] = &exp_lexer_set_special_param;
		else if (ft_isalpha(i) || i == '_')
			lexer->methods[EXP_STATE_DOLLAR][i] = &exp_lexer_set_var;
		else if (i == '{')
			lexer->methods[EXP_STATE_DOLLAR][i] = &exp_lexer_curly_expansion_start;
		else
			lexer->methods[EXP_STATE_DOLLAR][i] = &exp_lexer_dollar_fail;
		++i;
	}
	lexer->methods[EXP_STATE_CURLY_EXP]['}'] = &exp_lexer_cut_var;
	lexer->methods[EXP_STATE_CURLY_EXP]['{'] = &exp_lexer_curly_expansion_start;
	lexer->methods[EXP_STATE_DOLLAR]['('] = &exp_lexer_set_proc_sub;
	lexer->methods[EXP_STATE_PROC_SUB]['('] = &exp_lexer_set_ari;
}

int			init_exp_lexer(t_exp_lexer *lexer)
{
	int	i;

	ft_bzero(lexer, sizeof(*lexer));
	i = 0;
	while (i <= CHAR_MAX)
	{
		lexer->methods[EXP_STATE_WORD][i] = &exp_lexer_add_to_buff;
		lexer->methods[EXP_STATE_SQUOTE][i] = &exp_lexer_add_to_buff;
		lexer->methods[EXP_STATE_DQUOTE][i] = &exp_lexer_add_to_buff;
		lexer->methods[EXP_STATE_ESCAPED][i] = &exp_lexer_pop_add_to_buff;
		lexer->methods[EXP_STATE_ARI][i] = &exp_lexer_pop_ari;
		lexer->methods[EXP_STATE_ARI_PAREN][i] = &exp_lexer_add_to_buff;
		lexer->methods[EXP_STATE_TILDE][i] = &exp_lexer_add_to_buff;
		lexer->methods[EXP_STATE_PROC_SUB][i] = &exp_lexer_add_to_buff;
		++i;
	}
	lexer->methods[EXP_STATE_ARI]['('] = &exp_lexer_push_ari_paren;
	lexer->methods[EXP_STATE_ARI_PAREN]['('] = &exp_lexer_push_ari_paren;
	lexer->methods[EXP_STATE_ARI_PAREN][')'] = &exp_lexer_pop_ari_paren;
	set_exp_lexer_var_methods(lexer);
	set_exp_lexer_other(lexer);
	set_exp_lexer_dollar(lexer);
	if (exp_ss_push(lexer, EXP_STATE_WORD))
		return (1);
	return (0);
}
