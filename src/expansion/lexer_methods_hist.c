/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_hist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:18:50 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/12 21:36:47 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "libft.h"

static char	*exp_find_cmd(t_array *history, char *buf)
{
	int	idx;

	if (!history)
		return (NULL);
	if (ft_strequ(buf, "!"))
		idx = history->length - 1;
	else
		idx = fc_find_cmd(buf, history);
	if (idx > history->length - 1)
		idx = history->length - 1;
	return (history->data[idx]);
}

static int	exp_replace_history(t_line *line, t_exp_lexer *lexer, char *value)
{
	char	*pattern;

	if (!(pattern = ft_strjoin("!", lexer->var.buffer)))
		return (1);
	if (!(line->data = ft_replace_all(line->data, pattern, value, 1)))
		return (1);
	free(pattern);
	return (0);
}

int			exp_lexer_cut_hist(t_shell *shell, char c, int mask)
{
	char	*value;
	int		i;

	(void)mask;
	(void)c;
	if (shell->exp_lexer.var.pos)
	{
		value = exp_find_cmd(shell->history, shell->exp_lexer.var.buffer);
		if (value)
		{
			i = 0;
			while (value[i])
			{
				if (add_to_exp_buff(&shell->exp_lexer.buffer, value[i]))
					return (EXP_LEXER_RET_ERROR);
				++i;
				if (exp_replace_history(&shell->line, &shell->exp_lexer, value))
					return (EXP_LEXER_RET_ERROR);
			}
		}
		free(shell->exp_lexer.var.buffer);
		ft_bzero(&shell->exp_lexer.var, sizeof(shell->exp_lexer.var));
	}
	exp_ss_pop(&shell->exp_lexer);
	return (0);
}

int			exp_lexer_push_hist(t_shell *shell, char c, int mask)
{
	(void)c;
	if (!(mask & EXP_LEXER_MASK_HISTORY))
		return (exp_lexer_add_to_buff(shell, c, mask));
	if (exp_ss_push(&shell->exp_lexer, EXP_STATE_HIST))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}
