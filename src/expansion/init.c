/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:26:10 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 21:36:56 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "expand.h"
#include "libft.h"

static void	set_exp_lexer_var_methods(t_exp_lexer *lexer)
{
	int	i;

	i = 0;
	while (i < CHAR_MAX)
	{
		if (ft_isalnum(i) || i == '_')
			lexer->methods[EXP_STATE_VAR][i] = &exp_lexer_add_to_var;
		else
			lexer->methods[EXP_STATE_VAR][i] = &exp_lexer_cut_var;
		++i;
	}
}

int			init_exp_lexer(t_exp_lexer *lexer)
{
	int	i;

	ft_bzero(lexer, sizeof(*lexer));
	i = 0;
	while (i < CHAR_MAX)
	{
		lexer->methods[EXP_STATE_WORD][i] = &exp_lexer_add_to_buff;
		lexer->methods[EXP_STATE_SQUOTE][i] = &exp_lexer_add_to_buff;
		lexer->methods[EXP_STATE_DQUOTE][i] = &exp_lexer_add_to_buff;
		++i;
	}
	set_exp_lexer_var_methods(lexer);
	lexer->methods[EXP_STATE_WORD]['\''] = &exp_lexer_push_squote;
	lexer->methods[EXP_STATE_WORD]['"'] = &exp_lexer_push_dquote;
	lexer->methods[EXP_STATE_WORD]['$'] = &exp_lexer_push_var;
	lexer->methods[EXP_STATE_DQUOTE]['$'] = &exp_lexer_push_var;
	lexer->methods[EXP_STATE_DQUOTE]['"'] = &exp_lexer_pop_quote;
	lexer->methods[EXP_STATE_SQUOTE]['\''] = &exp_lexer_pop_quote;
	if (exp_ss_push(lexer, EXP_STATE_WORD))
		return (1);
	return (0);
}
