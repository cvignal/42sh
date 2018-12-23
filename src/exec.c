/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:03:28 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:44:56 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "21sh.h"
#include "libft.h"

static int	bin_not_found(const char *bin)
{
	ft_dprintf(2, "%s: %s: %s\n", EXEC_NAME, COMMAND_NOT_FOUND_MSG, bin);
	return (1);
}

static int	ft_wait(int *status)
{
	while (1)
	{
		wait(status);
		if (WIFEXITED(*status))
			return (0);
	}
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

int			exec(t_shell *shell, t_pipeline *pipeline, t_pipeline *current)
{
	pid_t		pid;
	char		*bin_path;
	t_builtin	builtin;

	if ((builtin = is_builtin(current->command->args[0])))
		return (exec_builtin(shell, builtin, current));
	bin_path = find_command(shell, current->command->args[0]);
	if (bin_path)
		pid = fork();
	else
		return (bin_not_found(current->command->args[0]));
	if (!pid)
	{
		apply_redirs(shell, current->command);
		open_close_pipe(pipeline, current);
		execve(bin_path, current->command->args, shell->env);
	}
	else
	{
		free(bin_path);
		current->command->pid = pid;
	}
	return (0);
}

int			wait_loop(t_pipeline *pipeline)
{
	int	status;

	status = 0;
	while (pipeline)
	{
		waitpid(pipeline->command->pid, &status, 0);
		if (WIFEXITED(status))
			pipeline = pipeline->next;
	}
	return (WEXITSTATUS(status));
}
