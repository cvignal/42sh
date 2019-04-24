/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:51:49 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 16:08:00 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static int	exit_error(const char *file, const char *msg)
{
	if (file)
		ft_dprintf(2, "%s: cd: %s: %s\n", EXEC_NAME, file, msg);
	else
		ft_dprintf(2, "%s: cd: %s\n", EXEC_NAME, msg);
	return (1);
}

static int	exit_error_cd(const char *file)
{
	char	type;

	if (access(file, F_OK))
		return (exit_error(file, "no such file or directory"));
	if (access(file, R_OK))
		return (exit_error(file, "permission denied"));
	type = file_type((char*)file);
	if (type != 'l' || type != 'd')
		return (exit_error(file, "not a directory"));
	return (1);
}

int			change_dir(t_shell *shell, char *curpath, char *dir, int option)
{
	char	*pwd;

	if (!(pwd = ft_strdup(get_env_value(shell, "PWD"))))
		pwd = getcwd(NULL, MAX_PATH);
	if (chdir(curpath))
	{
		free(pwd);
		return (exit_error_cd(curpath));
	}
	set_env_var(shell, "OLDPWD", pwd);
	free(pwd);
	if (option)
	{
		pwd = getcwd(NULL, MAX_PATH);
		set_env_var(shell, "PWD", pwd);
		free(pwd);
	}
	else
		set_env_var(shell, "PWD", curpath);
	free(curpath);
	return (0);
}

static int	cd_find_path(t_shell *shell, char *dir, int option)
{
	char	*curpath;
	char	*pwd;

	if (!dir)
		return (1);
	if (*dir == '/')
		curpath = ft_strdup(dir);
	else if (ft_strnequ(dir, "./", 2) || ft_strnequ(dir, "../", 3))
		curpath = ft_strdup(dir);
	else
		curpath = cd_parse_path(shell, dir);
	if (option)
		return (change_dir(shell, curpath, dir, option));
	else if (*curpath != '/')
	{
		if (!(pwd = ft_strdup(get_env_value(shell, "PWD"))))
			pwd = getcwd(NULL, MAX_PATH);
		if (pwd[ft_strlen(pwd) - 1] != '/')
			pwd = ft_strjoin_free(pwd, "/", 1);
		curpath = ft_strjoin_free(pwd, curpath, 3);
	}
	return (canonic_path(shell, curpath, dir, option));
}

int			builtin_cd(t_shell *shell, char **args)
{
	unsigned int	i;
	char			*dir;
	int				option;

	if ((i = cd_parse_options(args, &option)) == -1)
		return (1);
	if (args[i] && args[i + 1])
		return (exit_error(NULL, "too many arguments"));
	if (args[i] && ft_strequ(args[i], "-"))
	{
		if (!(dir = get_env_value(shell, "OLDPWD")))
			return (exit_error(NULL, "OLDPWD not set"));
		ft_dprintf(g_fd_output, "%s\n", dir);
		return (cd_find_path(shell, dir, option));
	}
	else if (args[i])
		return (cd_find_path(shell, args[i], option));
	if (!(dir = get_env_value(shell, "HOME")))
		return (exit_error(NULL, "HOME not set"));
	return (cd_find_path(shell, dir, option));
}
