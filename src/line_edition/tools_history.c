/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:47:09 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/11 19:18:10 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#include "shell.h"
#include "fill_line.h"
#include "libft.h"

static int	add_complete_command(char *str, t_shell *shell
		, char **multi_line, int fd_hf)
{
	int	len;

	if (*multi_line && !shell->prev_cmd_state)
	{
		if (!(*multi_line = ft_strjoin_free(*multi_line, str, 1)))
			return (1);
		len = shell->history->length - 1;
		ft_strdel(&shell->history->data[len]);
		if (!(shell->history->data[len] = ft_strdup(*multi_line)))
			return (1);
		ft_dprintf(fd_hf, "%10d:%s\n", time(NULL), *multi_line);
		ft_strdel(multi_line);
		return (0);
	}
	if (ft_arrayadd(shell->history, str))
		return (1);
	ft_dprintf(fd_hf, "%10d:%s\n", time(NULL), str);
	if (*multi_line && shell->prev_cmd_state)
		ft_strdel(multi_line);
	shell->prev_cmd_state = 0;
	return (0);
}

static int	add_incomplete_command(char *str, t_shell *shell, char **multi_line)
{
	int	len;

	if (*multi_line)
	{
		if (!(*multi_line = ft_strjoin_free(*multi_line, str, 1)))
			return (1);
		if (!(*multi_line = ft_strjoin_free(*multi_line, "\n", 1)))
			return (1);
		len = shell->history->length - 1;
		ft_strdel(&shell->history->data[len]);
		if (!(shell->history->data[len] = ft_strdup(*multi_line)))
			return (1);
	}
	else
	{
		if (!(*multi_line = ft_strjoin_free(str, "\n", 0)))
			return (1);
		if (ft_arrayadd(shell->history, str))
			return (1);
	}
	return (0);
}

int			add_to_history(char *str, t_shell *shell, int flag)
{
	static char	*multi_line = NULL;
	int			fd_hf;
	int			ret;

	if (check_validity(shell))
		return (0);
	if (flag)
		return (add_incomplete_command(str, shell, &multi_line));
	else if (!flag && ft_strlen(str) && !ft_strnequ(str, "\033[", 2))
	{
		if ((fd_hf = open(".shperso_history", O_RDWR | O_APPEND
					| O_CREAT, 0644)) == -1)
			return (1);
		ret = add_complete_command(str, shell, &multi_line, fd_hf);
		if (close(fd_hf) == -1)
			return (1);
		return (ret);
	}
	return (0);
}
