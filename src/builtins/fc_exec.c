/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:23:36 by cvignal           #+#    #+#             */
/*   Updated: 2019/07/09 17:37:23 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"
#include "jobs.h"

int			fc_switch_env(t_shell *new_shell, t_shell *shell)
{
	free_vars(&shell->vars);
	shell->vars = copy_vars(new_shell->vars, 0);
	free_vars(&new_shell->vars);
	return (0);
}

static void	expand_history_sub(t_shell *shell, char *str, int flag)
{
	shell->line.data = str;
	shell->line.len = ft_strlen(str);
	shell->line.alloc_size = ft_strlen(str) + 1;
	if (!flag)
		ft_dprintf(shell->fd_op, "%s%s%s\n", ORANGE, str, EOC);
	if (expand_history(shell))
	{
		free_line(&shell->line);
		shell->line.data = ft_strnew(0);
	}
}

int			fc_exec_line(char *str, t_shell *shell, int flag)
{
	t_shell tmp_shell;
	t_token	*tokens;

	if (fc_init_shell(&tmp_shell, shell))
		return (1);
	expand_history_sub(&tmp_shell, str, flag);
	if (!(tokens = lex(&tmp_shell, tmp_shell.line.data)))
	{
		free_shell(&tmp_shell);
		return (1);
	}
	fc_exec_ast(&tmp_shell, tokens, flag);
	job_notify(&tmp_shell);
	fc_free_shell(&tmp_shell);
	fc_switch_env(&tmp_shell, shell);
	return (0);
}

int			fc_exec_file(char *name, t_shell *shell)
{
	int		fd;
	char	*cmd;
	t_shell	tmp_shell;
	t_token	*tokens;

	if (fc_init_shell(&tmp_shell, shell))
		return (1);
	if ((fd = open(name, O_RDONLY)) == -1)
		return (1);
	while (get_next_line(fd, &cmd) > 0)
	{
		expand_history_sub(&tmp_shell, cmd, 0);
		if ((tokens = lex(&tmp_shell, tmp_shell.line.data)))
			fc_exec_ast(&tmp_shell, tokens, 0);
		free_line(&tmp_shell.line);
	}
	fc_free_shell(&tmp_shell);
	if (close(fd) == -1)
		return (1);
	fc_switch_env(&tmp_shell, shell);
	return (0);
}
