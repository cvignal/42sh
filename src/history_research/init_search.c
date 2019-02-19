/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_search.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 16:23:43 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/19 17:19:03 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "fill_line.h"

t_key	g_special_keys[] =\
{
	{LEFT_ARROW, &hs_leftkey},
	{RIGHT_ARROW, &hs_rightkey},
	{BACKSPACE, &hs_backspace},
	{DEL_KEY, &hs_delete},
	{TAB_KEY, &hs_tab},
	{DOWN_ARROW, &hs_hisdown},
	{UP_ARROW, &hs_hisup},
	{HOME_KEY, &hs_homekey},
	{END_KEY, &hs_endkey},
	{MAJ_LEFT, &hs_prevword},
	{MAJ_RIGHT, &hs_nextword},
	{MAJ_UP, &hs_lineup},
	{MAJ_DOWN, &hs_linedown},
	{F1_KEY, &hs_switch_mode},
	{F2_KEY, &hs_copy},
	{F3_KEY, &hs_paste},
	{F4_KEY, &hs_cut},
	{CTRL_D, &hs_ctrld},
	{CTRL_C, &ft_ctrlc},
	{CTRL_L, &hs_ctrll},
	{CTRL_R, &hs_ctrlr},
	{CTRL_A, &hs_homekey},
	{CTRL_HOME, &hs_homekey},
	{CTRL_END, &hs_endkey},
	{ALT_HOME, &hs_homekey},
	{ALT_END, &hs_endkey}
};

int	hs_specialkeys(char *buf)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (*buf == 127)
		return (1);
	while (i < sizeof(g_special_keys) / sizeof(*g_special_keys))
	{
		len = ft_strlen(g_special_keys[i].value);
		if (ft_strnequ(g_special_keys[i].value, buf, len))
			return (1);
		i++;
	}
	return (0);
}

int	ft_ctrlr(t_shell *shell)
{
	int		ret;
	char	buf[9];
	int		res;

	t_puts("cr");
	t_puts("dl");
	ft_printf("(reverse-i-search)`': ");
	ft_bzero(shell->line.search, SEARCH_MAX);
	res = 0;
	while ((ret = read(0, buf, 8) && !res))
	{
		buf[ret] = 0;
		if (hs_specialkeys(buf))
		{
			if (hs_keyapply(buf, shell))
				break ;
		}
		else
			res = hs_addchar(buf, shell);
	}
	return (0);
}
