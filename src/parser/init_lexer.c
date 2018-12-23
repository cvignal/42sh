/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:46:05 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 12:34:14 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

static void	init_lexer_meta(t_lexer *lexer, t_lstate state, t_lexer_act act)
{
	unsigned int	i;
	size_t			len_meta;

	len_meta = ft_strlen(META_CHARS);
	i = 0;
	while (i < len_meta)
	{
		lexer->lexer_actions[state][(int)META_CHARS[i]] = act;
		++i;
	}
}

static void	init_lexer_quote(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (i <= CHAR_MAX)
	{
		lexer->lexer_actions[LSTATE_SQUOTE][i] = &lexer_add;
		lexer->lexer_actions[LSTATE_DQUOTE][i] = &lexer_add;
		++i;
	}
	lexer->lexer_actions[LSTATE_NONE]['\''] = &lexer_create_squote;
	lexer->lexer_actions[LSTATE_SQUOTE]['\''] = &lexer_cut_pass;
	lexer->lexer_actions[LSTATE_NONE]['"'] = &lexer_create_dquote;
	lexer->lexer_actions[LSTATE_DQUOTE]['"'] = &lexer_cut_pass;
}

static void	init_lexer_zero(t_lexer *lexer)
{
	lexer->lexer_actions[LSTATE_WORD][0] = &lexer_cut;
	lexer->lexer_actions[LSTATE_VAR][0] = &lexer_pop_var;
	lexer->lexer_actions[LSTATE_NONE][0] = &lexer_over;
	lexer->lexer_actions[LSTATE_DQUOTE][0] = &lexer_more_input;
	lexer->lexer_actions[LSTATE_SQUOTE][0] = &lexer_more_input;
}

int			init_lexer(t_lexer *lexer)
{
	int	i;

	if (lss_push(lexer, LSTATE_NONE))
		return (1);
	i = 0;
	while (i <= CHAR_MAX)
	{
		lexer->lexer_actions[LSTATE_NONE][i] = &lexer_create;
		lexer->lexer_actions[LSTATE_WORD][i] = &lexer_add;
		lexer->lexer_actions[LSTATE_META][i] = &lexer_try_meta;
		lexer->lexer_actions[LSTATE_VAR][i] = &lexer_add;
		++i;
	}
	init_lexer_quote(lexer);
	init_lexer_zero(lexer);
	lexer->lexer_actions[LSTATE_WORD][' '] = &lexer_cut;
	lexer->lexer_actions[LSTATE_WORD]['\t'] = &lexer_cut;
	lexer->lexer_actions[LSTATE_VAR][' '] = &lexer_pop_var;
	lexer->lexer_actions[LSTATE_VAR]['\t'] = &lexer_pop_var;
	lexer->lexer_actions[LSTATE_VAR]['\''] = &lexer_pop_var;
	lexer->lexer_actions[LSTATE_VAR]['"'] = &lexer_pop_var;
	lexer->lexer_actions[LSTATE_NONE][' '] = &lexer_pass;
	lexer->lexer_actions[LSTATE_NONE]['\t'] = &lexer_pass;
	lexer->lexer_actions[LSTATE_WORD]['$'] = &lexer_push_var;
	lexer->lexer_actions[LSTATE_DQUOTE]['$'] = &lexer_push_var;
	init_lexer_meta(lexer, LSTATE_NONE, &lexer_create_meta);
	init_lexer_meta(lexer, LSTATE_META, &lexer_add_meta);
	init_lexer_meta(lexer, LSTATE_WORD, &lexer_try_meta);
	init_lexer_meta(lexer, LSTATE_VAR, &lexer_pop_var);
	return (0);
}
