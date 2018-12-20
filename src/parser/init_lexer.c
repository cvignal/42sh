/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:46:05 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/15 22:13:29 by gchainet         ###   ########.fr       */
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

void		init_lexer(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (i <= CHAR_MAX)
		lexer->lexer_actions[LSTATE_NONE][i++] = &lexer_create;
	i = 0;
	while (i <= CHAR_MAX)
		lexer->lexer_actions[LSTATE_WORD][i++] = &lexer_add;
	i = 0;
	while (i <= CHAR_MAX)
		lexer->lexer_actions[LSTATE_META][i++] = &lexer_cut;
	lexer->lexer_actions[LSTATE_WORD][' '] = &lexer_cut;
	lexer->lexer_actions[LSTATE_WORD]['\t'] = &lexer_cut;
	lexer->lexer_actions[LSTATE_NONE][' '] = &lexer_pass;
	lexer->lexer_actions[LSTATE_NONE]['\t'] = &lexer_pass;
	init_lexer_meta(lexer, LSTATE_NONE, &lexer_create_meta);
	init_lexer_meta(lexer, LSTATE_META, &lexer_add_meta);
	init_lexer_meta(lexer, LSTATE_WORD, &lexer_cut);
}
