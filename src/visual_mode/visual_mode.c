/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:31:14 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/11 21:06:21 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "fill_line.h"

static const t_key	g_vm_keys[] =\
{
	{LEFT_ARROW, &vm_leftkey},
	{RIGHT_ARROW, &vm_rightkey},
	{HOME_KEY, &vm_homekey},
	{END_KEY, &vm_endkey},
	{"y", &vm_copy},
	{"d", &vm_cut}
};

static int			vm_special_keys(char *buf)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (ft_strequ(F1_KEY, buf))
		return (1);
	while (i < sizeof(g_vm_keys) / sizeof(*g_vm_keys))
	{
		len = ft_strlen(g_vm_keys[i].value);
		if (ft_strnequ(g_vm_keys[i].value, buf, len))
			return (1);
		i++;
	}
	return (0);
}

static int			apply_vm_key(char *buf, t_shell *shell)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (ft_strequ(F1_KEY, buf))
		return (1);
	while (i < sizeof(g_vm_keys) / sizeof(*g_vm_keys))
	{
		len = ft_strlen(g_vm_keys[i].value);
		if (ft_strnequ(g_vm_keys[i].value, buf, len))
			return (g_vm_keys[i].f(shell));
		i++;
	}
	return (0);
}

int					visual_mode(t_shell *shell)
{
	char	buf[9];
	int		res;
	int		ret;

	res = 0;
	if (shell->line.cursor < shell->line.len)
	{
		ft_dprintf(shell->fd_op, "%s%c%s", INV_COLOR
			, shell->line.data[shell->line.cursor], EOC);
		t_puts("le");
	}
	shell->line.select_curs = shell->line.cursor;
	while (!res && (ret = read(0, buf, 8)) >= 0)
	{
		buf[ret] = 0;
		if (vm_special_keys(buf))
			res = apply_vm_key(buf, shell);
	}
	clear_cmd_line(shell);
	if (shell->line.data)
		ft_dprintf(g_fd_output, "%s", shell->line.data);
	shell->line.cursor = shell->line.len;
	return (0);
}
