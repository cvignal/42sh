/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_hist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:18:50 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/06 15:50:33 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include "libft.h"
#include "fill_line.h"

static int	find_event(char *str, t_array *history)
{
	int		i;
	size_t	len;
	int		nb;

	if (!history)
		return (0);
	if (ft_isdigit(str[0]) || str[0] == '-')
	{
		nb = ft_atoi(str);
		if (nb < 0 && history->length + nb >= 0)
			nb += history->length;
		else if (history->length + nb < 0)
			nb = -1;
		return (nb);
	}
	i = history->length - 1;
	len = ft_strlen(str);
	while (i > 0)
	{
		if (ft_strnequ(str, history->data[i], len))
			return (i);
		i--;
	}
	return (-1);
}

char		*exp_find_cmd(t_array *history, char *buf)
{
	int	idx;

	if (!history)
		return (NULL);
	if (ft_strequ(buf, "!"))
		idx = history->length - 1;
	else
		idx = find_event(buf, history);
	if (idx == -1)
	{
		ft_dprintf(2, "\n%s: !%s: event not found", EXEC_NAME, buf);
		return (NULL);
	}
	return (history->data[idx]);
}

static int	return_expand(t_shell *shell)
{
	if (shell->fc_rec)
		return (0);
	clear_cmd_line(shell);
	print_line_bis(shell);
	return (0);
}

static int	main_loop(t_shell *shell, char *str, t_pars_hist *flags)
{
	char	c;

	c = str[flags->idx];
	if (c == '\\' && !flags->backslash)
		flags->backslash = 1;
	else if (c == '\'' && !flags->squote && !flags->backslash)
		flags->squote = 1;
	else if (c == '\'' && flags->squote && !flags->backslash)
		flags->squote = 0;
	else if (ft_strnequ(str + flags->idx, "$((", 3)
			&& !flags->squote && !flags->backslash)
		flags->arit = 1;
	else if (ft_strnequ(str + flags->idx, "))", 2) && flags->arit)
		flags->arit = 0;
	else if (c == '!' && !flags->squote && !flags->backslash)
	{
		if ((flags->idx = replace_exclamation_mark(shell, flags->idx, flags->arit)) == -1)
			return (1);
	}
	else if (flags->backslash)
		flags->backslash = 0;
	return (0);
}

int			expand_history(t_shell *shell)
{
	t_pars_hist flags;
	char		c;

	ft_bzero(&flags, sizeof(flags));
	while ((c = shell->line.data[flags.idx]))
	{
		if (main_loop(shell, shell->line.data, &flags))
			return (1);
		flags.idx++;
	}
	return (return_expand(shell));
}
