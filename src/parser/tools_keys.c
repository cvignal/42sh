/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:48:05 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/24 17:40:37 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <curses.h>

#include "libft.h"
#include "21sh.h"
#include "fill_line.h"

t_key	g_special_keys[] =
{
	{LEFT_ARROW, &ft_leftkey},
	{RIGHT_ARROW, &ft_rightkey},
	{BACKSPACE, &ft_backspace},
	{TAB_KEY, &ft_tab},
	{DOWN_ARROW, &ft_hisdown},
	{UP_ARROW, &ft_hisup},
	{HOME_KEY, &ft_homekey},
	{END_KEY, &ft_endkey},
	{F1_KEY, &ft_prevword},
	{F2_KEY, &ft_nextword}
};

int		is_a_special_key(char *buf)
{
	return (!(*buf > 31 && *buf < 127));
}

int		ft_printchar(int c)
{
	return (write(1, &c, 1));
}

void	ft_addchar(t_shell *shell, char *buf)
{
	if (shell->cursor == ft_strlen(shell->line))
	{
		shell->line = ft_strjoin_free(shell->line, buf, 1);
		ft_printf("%s", buf);
	}
	else
	{
		tputs(tgetstr("im", NULL), 1, ft_printchar);
		ft_printf("%s", buf);
		shell->line = ft_insert_free(shell->line, buf, shell->cursor, 1);
		tputs(tgetstr("ei", NULL), 1, ft_printchar);
	}
	shell->cursor++;
}

void	apply_key(char *buf, t_shell *shell)
{
	int		i;
	size_t	len;

	i = 0;
	if (*buf == 127)
		ft_backspace(shell);
	while (i < 10)
	{
		len = ft_strlen(g_special_keys[i].value);
		if (ft_strnequ(g_special_keys[i].value, buf, len))
			g_special_keys[i].f(shell);
		i++;
	}
}
