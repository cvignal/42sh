/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:46:05 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 13:52:03 by gchainet         ###   ########.fr       */
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
	lexer->lexer_actions[LSTATE_WORD]['\''] = &lexer_push_squote;
	lexer->lexer_actions[LSTATE_SQUOTE]['\''] = &lexer_pop_quote;
	lexer->lexer_actions[LSTATE_WORD]['"'] = &lexer_push_dquote;
	lexer->lexer_actions[LSTATE_DQUOTE]['"'] = &lexer_pop_quote;
}

static void	init_lexer_zero(t_lexer *lexer)
{
	lexer->lexer_actions[LSTATE_WORD][0] = &lexer_cut;
	lexer->lexer_actions[LSTATE_NONE][0] = &lexer_over;
	lexer->lexer_actions[LSTATE_DQUOTE][0] = &lexer_more_input;
	lexer->lexer_actions[LSTATE_SQUOTE][0] = &lexer_more_input;
	lexer->lexer_actions[LSTATE_META][0] = &lexer_cut;
}

static void	init_lexer_basics(t_lexer *lexer)
{
	lexer->lexer_actions[LSTATE_WORD][' '] = &lexer_cut;
	lexer->lexer_actions[LSTATE_WORD]['\t'] = &lexer_cut;
	lexer->lexer_actions[LSTATE_NONE][' '] = &lexer_pass;
	lexer->lexer_actions[LSTATE_NONE]['\t'] = &lexer_pass;
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
		++i;
	}
	init_lexer_quote(lexer);
	init_lexer_zero(lexer);
	init_lexer_basics(lexer);
	init_lexer_meta(lexer, LSTATE_NONE, &lexer_create_meta);
	init_lexer_meta(lexer, LSTATE_META, &lexer_add_meta);
	init_lexer_meta(lexer, LSTATE_WORD, &lexer_try_meta);
	return (0);
}
