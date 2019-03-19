/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_hist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:18:50 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/19 16:54:29 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "libft.h"

static char	*exp_find_cmd(t_array *history, char *buf)
{
	int	idx;

	if (ft_strequ(buf, "!"))
		idx = history->length - 1;
	else
		idx = fc_find_cmd(buf, history);
	if (idx > history->length - 1)
		idx = history->length - 1;
	return (history->data[idx]);
}

int			exp_lexer_cut_hist(t_shell *shell, t_exp_lexer *lexer, char c)
{
	char	*value;
	int		i;

	(void)c;
	if (lexer->var.pos)
	{
		value = exp_find_cmd(shell->history, lexer->var.buffer);
		if (value)
		{
			i = 0;
			while (value[i])
			{
				if (add_to_exp_buff(&lexer->buffer, value[i]))
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

int			exp_lexer_push_hist(t_shell *shell, t_exp_lexer *lexer, char c)
{
	(void)shell;
	(void)c;
	if (exp_ss_push(lexer, EXP_STATE_HIST))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}
