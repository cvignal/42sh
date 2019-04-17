/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 12:23:36 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/11 13:59:16 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

int		fc_switch_env(t_shell *new_shell, t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->env)
	{
		while (shell->env[i])
			free(shell->env[i++]);
		free(shell->env);
	}
	shell->env = new_shell->env;
	return (0);
}

int		fc_exec_line(char *str, t_shell *shell)
{
	t_shell tmp_shell;
	t_token	*tokens;

	if (fc_init_shell(&tmp_shell, shell))
		return (1);
	if (ft_addchar(&tmp_shell, str, 1))
		return (1);
	ft_printf("\n");
	if (!(tokens = lex(&tmp_shell)))
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
		ft_addchar(&tmp_shell, cmd, 1);
		ft_printf("\n");
		if ((tokens = lex(&tmp_shell)))
			fc_exec_ast(&tmp_shell, tokens);
		free_line(&tmp_shell.line);
		free(cmd);
	}
	fc_free_shell(&tmp_shell);
	if (close(fd) == -1)
		return (1);
	fc_switch_env(&tmp_shell, shell);
	return (0);
}
