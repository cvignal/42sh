/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 13:48:05 by cvignal           #+#    #+#             */
/*   Updated: 2019/02/26 17:39:59 by cvignal          ###   ########.fr       */
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
	{DEL_KEY, &ft_delete},
	{TAB_KEY, &ft_tab},
	{DOWN_ARROW, &ft_hisdown},
	{UP_ARROW, &ft_hisup},
	{HOME_KEY, &ft_homekey},
	{END_KEY, &ft_endkey},
	{MAJ_LEFT, &ft_prevword},
	{MAJ_RIGHT, &ft_nextword},
	{MAJ_UP, &ft_lineup},
	{MAJ_DOWN, &ft_linedown},
	{F1_KEY, &visual_mode},
	{CTRL_P, &ft_paste},
	{CTRL_D, &ft_ctrld},
	{CTRL_C, &ft_ctrlc},
	{CTRL_L, &ft_ctrll},
	{CTRL_R, &ft_ctrlr},
	{CTRL_A, &ft_homekey},
	{CTRL_HOME, &ft_homekey},
	{CTRL_END, &ft_endkey},
	{ALT_HOME, &ft_homekey},
	{ALT_END, &ft_endkey}
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
	return (write(g_fd_output, &c, 1));
}

int		t_puts(char *id)
{
	char	*str;

	if (!(str = tgetstr(id, NULL)))
		return (1);
	if (tputs(str, 0, ft_printchar) == ERR)
		return (1);
	return (0);
}

int		ft_addchar(t_shell *shell, char *buf, int flag)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if ((buf[i] == 10 || buf[i] == 13) && !flag)
			return (1);
		else if ((buf[i] >= 32 && buf[i] <= 126) || (buf[i] == 10 && flag))
		{
			if (add_to_line(&shell->line, buf[i]))
			{
				ft_dprintf(2, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
				return (-1);
			}
			print_line(shell, buf[i]);
		}
		i++;
	}
	return (0);
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
