/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:48:05 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/01 14:10:41 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <term.h>
#include <curses.h>

#include "libft.h"
#include "shell.h"
#include "fill_line.h"

t_key	g_special_keys[] =\
{
	{LEFT_ARROW, &ft_leftkey},
	{RIGHT_ARROW, &ft_rightkey},
	{BACKSPACE, &ft_backspace},
	{DEL_KEY, &ft_backspace},
	{TAB_KEY, &ft_tab},
	{DOWN_ARROW, &ft_hisdown},
	{UP_ARROW, &ft_hisup},
	{HOME_KEY, &ft_homekey},
	{END_KEY, &ft_endkey},
	{MAJ_LEFT, &ft_prevword},
	{MAJ_RIGHT, &ft_nextword},
	{MAJ_UP, &ft_lineup},
	{MAJ_DOWN, &ft_linedown},
	{F1_KEY, &ft_switch_mode},
	{F2_KEY, &ft_copy},
	{F3_KEY, &ft_paste},
	{F4_KEY, &ft_cut},
	{CTRL_D, &ft_ctrld},
	{CTRL_C, &ft_ctrlc},
	{CTRL_L, &ft_ctrll},
	{CTRL_R, &ft_ctrlr}
};

int		is_a_special_key(char *buf)
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

int		apply_key(char *buf, t_shell *shell)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (*buf == 127)
		return (ft_backspace(shell));
	while (i < sizeof(g_special_keys) / sizeof(*g_special_keys))
	{
		len = ft_strlen(g_special_keys[i].value);
		if (ft_strnequ(g_special_keys[i].value, buf, len))
			return (g_special_keys[i].f(shell));
		i++;
	}
	return (0);
}