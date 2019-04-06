/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:33:40 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/06 04:01:29 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "parser.h"
#include "arithmetic.h"

static inline void	init_arithmetic_alnum(t_lexer *lexer, int i)
{
	lexer->lexer_actions[LSTATE_ARI_NONE][i] = &alexer_create;
	lexer->lexer_actions[LSTATE_ARI_ID][i] = &alexer_add;
	lexer->lexer_actions[LSTATE_ARI_OP][i] = &alexer_cut;
	lexer->lexer_actions[LSTATE_ARI_PAREN][i] = &alexer_create;
}

static inline void	init_arithmetic_op(t_lexer *lexer, int i)
{
	lexer->lexer_actions[LSTATE_ARI_NONE][i] = &alexer_create;
	lexer->lexer_actions[LSTATE_ARI_ID][i] = &alexer_cut;
	lexer->lexer_actions[LSTATE_ARI_OP][i] = &alexer_try_op;
	lexer->lexer_actions[LSTATE_ARI_PAREN][i] = &alexer_create;
}

static inline void	init_arithmetic_other(t_lexer *lexer, int i)
{
	if (i == '$')
		lexer->lexer_actions[LSTATE_ARI_NONE][i] = &alexer_create;
	else
		lexer->lexer_actions[LSTATE_ARI_NONE][i] = &alexer_input_error;
	lexer->lexer_actions[LSTATE_ARI_ID][i] = &alexer_cut;
	lexer->lexer_actions[LSTATE_ARI_OP][i] = &alexer_cut;
	lexer->lexer_actions[LSTATE_ARI_PAREN][i] = &alexer_cut;
}

static inline void	init_arithmetic_parenthesis(t_lexer *lexer)
{
	lexer->lexer_actions[LSTATE_ARI_NONE][(int)'('] = &alexer_push_paren;
	lexer->lexer_actions[LSTATE_ARI_ID][(int)'('] = &alexer_cut;
	lexer->lexer_actions[LSTATE_ARI_OP][(int)'('] = &alexer_cut;
	lexer->lexer_actions[LSTATE_ARI_PAREN][(int)')'] = &alexer_pop_paren;
	lexer->lexer_actions[LSTATE_ARI_NONE][(int)')'] = &alexer_check_end;
	lexer->lexer_actions[LSTATE_ARI_ID][(int)')'] = &alexer_cut;
	lexer->lexer_actions[LSTATE_ARI_OP][(int)')'] = &alexer_try_op;
}

int					init_arithmetic_lexer(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (i <= CHAR_MAX)
	{
		if (ft_isalnum(i) || i == '_')
			init_arithmetic_alnum(lexer, i);
		else if (is_operator_char(i))
			init_arithmetic_op(lexer, i);
		else
			init_arithmetic_other(lexer, i);
		++i;
	}
	init_arithmetic_parenthesis(lexer);
	return (0);
}
