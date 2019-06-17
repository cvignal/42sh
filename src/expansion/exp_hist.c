/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_hist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 16:18:50 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/17 12:29:51 by cvignal          ###   ########.fr       */
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

static void	init_parsing_hist(int *backslash, int *i, int *squote)
{
	*backslash = 0;
	*i = 0;
	*squote = 0;
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

int			expand_history(t_shell *shell)
{
	int	i;
	int	backslash;
	int	squote;

	init_parsing_hist(&backslash, &i, &squote);
	while (shell->line.data[i])
	{
		if (shell->line.data[i] == '\\' && !backslash)
			backslash = 1;
		else if (shell->line.data[i] == '\'' && !squote && !backslash)
			squote = 1;
		else if (shell->line.data[i] == '\'' && squote && !backslash)
			squote = 0;
		else if (shell->line.data[i] == '!' && !squote && !backslash)
		{
			if ((i = replace_exclamation_mark(shell, i)) == -1)
				return (1);
		}
		else if (backslash)
			backslash = 0;
		i++;
	}
	clear_cmd_line(shell);
	print_line_bis(shell);
	return (0);
}
