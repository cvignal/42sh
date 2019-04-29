/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:03:28 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/28 18:02:22 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#include "shell.h"
#include "jobs.h"
#include "fill_line.h"
#include "libft.h"
#include "expand.h"

static void	exec_internal(t_shell *shell, t_ast *instr,
	const char *path, t_builtin builtin)
{
	char **args;

	if (!instr->job->pgid)
		instr->job->pgid = instr->pid;
	setpgid(instr->pid, instr->job->pgid);
	if (instr->flags & (CMD_ASYNC | CMD_FORK))
		tcsetpgrp(0, instr->job->pgid);
	set_pipeline(shell, instr);
	if (apply_redirs(shell, instr))
	{
		free_shell(shell);
		exit(127);
	}
	args = ((t_command *)instr->data)->args_value;
	if (builtin)
		exit(builtin(shell, args));
	enable_signal();
	exit(execve(path, args, build_env(shell->exec_vars)));
}

pid_t		do_exec(t_shell *shell, char **argv)
{
	int			status;
	pid_t		pid;
	char		*bin_path;

	if (!(bin_path = find_command(shell->vars, argv[0])))
		return (do_error_handling(argv[0]));
	if ((pid = fork()) == -1)
		return (-1);
	if (pid == 0)
		exit(execve(bin_path, argv, build_env(shell->exec_vars)));
	free(bin_path);
	wait(&status);
	if (WIFEXITED(status) || WIFSIGNALED(status))
		return (0);
	return (WEXITSTATUS(status));
}

pid_t		exec(t_shell *shell, t_ast *instr)
{
	char		*prgm;
	char		*bin_path;
	t_builtin	builtin;

	prgm = ((t_command *)instr->data)->args_value[0];
	if (!(builtin = is_builtin(prgm))
		&& !(bin_path = hbt_command(shell, prgm)))
	{
		instr->ret = do_error_handling(prgm);
		return (-1);
	}
	if (!builtin || instr->flags & CMD_FORK)
	{
		if ((instr->pid = fork()) == -1)
			return (-1);
	}
	else
		return (exec_builtin(shell, builtin, instr));
	if (instr->pid == 0)
		exec_internal(shell, instr, bin_path, builtin);
	register_proc(instr);
	return (0);
}
