/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:03:28 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/14 17:56:03 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"
#include "fill_line.h"
#include "libft.h"
#include "expand.h"

static int	bin_not_found(const char *bin)
{
	ft_dprintf(2, "%s: %s: %s\n", EXEC_NAME, COMMAND_NOT_FOUND_MSG, bin);
	return (-1);
}

static int	ft_wait(int *status)
{
	while (1)
	{
		wait(status);
		if (WIFEXITED(*status) || WIFSIGNALED(*status))
			return (0);
	}
}

static void	exec_internal(t_shell *shell, t_ast *instr, const char *bin_path)
{
	set_pipeline(shell, instr);
	if (expand_params(shell, instr->data) || apply_redirs(shell, instr))
	{
		free_shell(shell);
		exit(1);
	}
	reset_terminal_mode(shell);
	enable_signal();
	execve(bin_path, ((t_command *)instr->data)->args_value, shell->env);
	exit(1);
}

int			exec_from_char(t_shell *shell, char **args, t_shell *tmp_shell)
{
	pid_t		pid;
	int			status;
	char		*bin_path;

	if (get_env_value(tmp_shell, "PATH"))
		bin_path = find_command(tmp_shell, args[0]);
	else
		bin_path = find_command(shell, args[0]);
	if (bin_path)
		pid = fork();
	else
		return (bin_not_found(args[0]));
	if (!pid)
		execve(bin_path, args, tmp_shell->env);
	else
	{
		free(bin_path);
		ft_wait(&status);
	}
	return (WEXITSTATUS(status));
}

pid_t		exec(t_shell *shell, t_ast *instr)
{
	pid_t		pid;
	char		*bin_path;
	t_builtin	builtin;

	if ((builtin = is_builtin(((t_command *)instr->data)->args[0])))
		return (exec_builtin(shell, builtin, instr));
	bin_path = hbt_command(shell, ((t_command *)instr->data)->args[0]);
	if (bin_path)
		pid = fork();
	else
	{
		instr->ret = 1;
		return (bin_not_found(((t_command *)instr->data)->args[0]));
	}
	if (!pid)
		exec_internal(shell, instr, bin_path);
	else
		instr->pid = pid;
	return (0);
}
