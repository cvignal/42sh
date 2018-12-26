/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:48:05 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/26 20:17:14 by cvignal          ###   ########.fr       */
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
	{F2_KEY, &ft_nextword},
	{MAJ_UP, &ft_lineup},
	{MAJ_DOWN, &ft_linedown}
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
	tputs(tgetstr("im", NULL), 1, ft_printchar);
	if (add_to_line(&shell->line, buf))
		ft_dprintf(2, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
	else
		ft_printf("%s", buf);
	tputs(tgetstr("ei", NULL), 1, ft_printchar);
}

void	apply_key(char *buf, t_shell *shell)
{
	int		i;
	size_t	len;

	i = 0;
	if (*buf == 127)
		ft_backspace(shell);
	while (i < 12)
	{
		len = ft_strlen(g_special_keys[i].value);
		if (ft_strnequ(g_special_keys[i].value, buf, len))
			g_special_keys[i].f(shell);
		i++;
	}
}
