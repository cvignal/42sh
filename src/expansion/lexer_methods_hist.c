/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_hist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:18:50 by cvignal           #+#    #+#             */
/*   Updated: 2019/05/07 13:59:47 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "libft.h"

char	*exp_find_cmd(t_array *history, char *buf)
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

int	exp_replace_history(t_line *line, t_exp_lexer *lexer, char *value)
{
	char	*pattern;

	if (!(pattern = ft_strjoin("!", lexer->var.buffer)))
		return (1);
	if (!(line->data = ft_replace_all(line->data, pattern, value, 1)))
		return (1);
	free(pattern);
	return (0);
}

int			replace_exclamation_mark(t_shell *shell, int i)
{
	int		j;
	int 	buf_size;
	char	*buf;

	j = i + 1;
	buf_size = 0;
	while (shell->line.data[j] != ' ' && !ft_strchr(META_CHARS, shell->line.data[j]))
	{
		j++;
		buf_size++;
	}
	if (!(buf = ft_strsub(shell->line.data, i, buf_size + 1)))
		return (-1);
	ft_strdel(&buf);
	return (buf_size);
}

int			expand_history(t_shell *shell)
{
	int	i;
	int	backslash;
	int	squote;

	backslash = 0;
	squote = 0;
	i = 0;
	while (shell->line.data[i])
	{
		if (shell->line.data[i] == '\\' && !backslash)
			backslash = 1;
		else if (shell->line.data[i] == '\'' && !squote && !backslash)
			squote = 1;
		else if (shell->line.data[i] == '\'' && squote && !backslash)
			squote = 0;
		else if (shell->line.data[i] == '!' && !squote && !backslash)
			i += replace_exclamation_mark(shell, i);
		else if (backslash)
			backslash = 0;
		i++;
	}
	return (0);
}
