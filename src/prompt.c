/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/29 16:13:43 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/08 14:54:55 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/ioctl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static void	print_special_prompt(t_shell *shell, char *str)
{
	t_curs	cursor;
	int		n;

	if (ioctl(0, FIONREAD, &n) == 0 && n > 0)
	{
		ft_dprintf(shell->fd_op, "%s%s%s %s[ %s ]%s ", YELLOW, "\xE2\x86\xAA"
			, EOC, !shell->ret_cmd ? GREEN : RED, str, EOC);
		return ;
	}
	get_cursor_pos(&cursor);
	if (cursor.col != 1)
		ft_dprintf(shell->fd_op, "%s%%%s\n", INV_COLOR, EOC);
	ft_dprintf(shell->fd_op, "%s%s%s %s[ %s ]%s ", YELLOW, "\xE2\x86\xAA"
		, EOC, !shell->ret_cmd ? GREEN : RED, str, EOC);
}

void		print_prompt(t_parser *parser, t_shell *shell, int flag)
{
	char	*cwd;
	char	*str;

	if (check_validity(shell))
		return ;
	raw_terminal_mode(shell);
	cwd = getcwd(NULL, MAX_PATH);
	if ((parser && parser->pss->state != PS_NONE) || flag
			|| shell->ret_cmd == -1)
	{
		shell->prompt_len = 2;
		ft_dprintf(shell->fd_op, "%s ", INCOMPLETE_INPUT_PROMPT);
		shell->ret_cmd = -1;
	}
	else
	{
		if (ft_strrchr(cwd, '/') && ft_strchr(cwd, '/') != ft_strrchr(cwd, '/'))
			str = ft_strrchr(cwd, '/') + 1;
		else
			str = cwd;
		shell->prompt_len = ft_strlen(str) + 7;
		print_special_prompt(shell, str);
	}
	free(cwd);
}
