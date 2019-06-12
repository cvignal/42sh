/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:23:36 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/12 17:49:54 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

int		fc_switch_env(t_shell *new_shell, t_shell *shell)
{
	free_vars(&shell->vars);
	shell->vars = copy_vars(new_shell->vars, 0);
	return (0);
}

int		fc_exec_line(char *str, t_shell *shell)
{
	t_shell tmp_shell;
	t_token	*tokens;

	if (fc_init_shell(&tmp_shell, shell))
		return (1);
	tmp_shell.line.data = str;
	ft_dprintf(shell->fd_op, "%s%s%s\n", ORANGE, str, EOC);
	if (!(tokens = lex(&tmp_shell, tmp_shell.line.data)))
	{
		free_shell(&tmp_shell);
		return (1);
	}
	fc_exec_ast(&tmp_shell, tokens);
	fc_free_shell(&tmp_shell);
	fc_switch_env(&tmp_shell, shell);
	return (0);
}

int		fc_exec_file(char *name, t_shell *shell)
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
		tmp_shell.line.data = cmd;
		ft_dprintf(shell->fd_op, "%s%s%s\n", ORANGE, cmd, EOC);
		if ((tokens = lex(&tmp_shell, tmp_shell.line.data)))
			fc_exec_ast(&tmp_shell, tokens);
		free_line(&tmp_shell.line);
	}
	fc_free_shell(&tmp_shell);
	if (close(fd) == -1)
		return (1);
	fc_switch_env(&tmp_shell, shell);
	return (0);
}
