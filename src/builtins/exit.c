/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 08:45:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/13 17:33:56 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>

#include "shell.h"
#include "jobs.h"
#include "fill_line.h"
#include "libft.h"

static int	exit_value(t_shell *shell, char **args)
{
	int		ret;

	if (args && args[1] && !ft_isdigit(args[1][0]) && args[1][0] != '-'
			&& args[1][0] != '+')
	{
		free_shell(shell);
		exit(255);
	}
	if (args && args[1])
	{
		ret = ft_atoi(args[1]);
		free_shell(shell);
		exit(ret);
	}
	else
	{
		ret = ft_atoi(get_var_value(get_var(shell->vars, SPECIAL_VAR_RET)));
		free_shell(shell);
		exit(ret);
	}
}

void		delete_fc_folder(void)
{
	DIR				*dir;
	struct dirent	*dirent;
	char			*path;

	if (!(dir = opendir("/tmp/folder_fc_builtin")))
		return ;
	while ((dirent = readdir(dir)))
	{
		if (!ft_strequ(dirent->d_name, ".") && !ft_strequ(dirent->d_name, ".."))
		{
			path = ft_strjoin("/tmp/folder_fc_builtin/", dirent->d_name);
			unlink(path);
			free(path);
		}
	}
	closedir(dir);
	rmdir("/tmp/folder_fc_builtin");
}

static int	verif_children(t_shell *shell)
{
	t_job *job;

	if (shell->last_cmd != builtin_exit)
	{
		job = shell->jobs;
		while (job)
		{
			if (job->state == JOB_STOPPED)
			{
				ft_dprintf(2, "There are stopped jobs.\n");
				return (1);
			}
			job = job->next;
		}
	}
	return (0);
}

int			builtin_exit(t_shell *shell, char **args)
{
	size_t	arg_count;

	if (verif_children(shell))
		return (1);
	arg_count = 0;
	while (args && args[arg_count])
		++arg_count;
	if (arg_count > 2)
	{
		ft_dprintf(2, "%s: exit: too many arguments\n", EXEC_NAME);
		return (1);
	}
	add_to_history(shell->line.data, shell, 0);
	delete_fc_folder();
	if (close(shell->fd_op) == -1)
		ft_dprintf(2, "Error on closing the tty fd\n");
	return (exit_value(shell, args));
}
