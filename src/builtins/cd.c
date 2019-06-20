/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:51:49 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/13 17:39:35 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static int	exit_error(char *file, const char *msg)
{
	if (file)
		ft_dprintf(2, "%s: cd: %s: %s\n", EXEC_NAME, file, msg);
	else
		ft_dprintf(2, "%s: cd: %s\n", EXEC_NAME, msg);
	free(file);
	return (1);
}

static int	exit_error_cd(char *file)
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

int			change_dir(t_shell *shell, char *curpath,
		const char *dir, int option)
{
	char	*pwd;

	(void)dir;
	if (!(pwd = ft_strdup(get_var_value(get_var(shell->exec_vars, "PWD")))))
		pwd = getcwd(NULL, MAX_PATH);
	if (chdir(curpath))
	{
		free(pwd);
		return (exit_error_cd(curpath));
	}
	set_var(&shell->vars, "OLDPWD", pwd, 1);
	free(pwd);
	if (option)
	{
		pwd = getcwd(NULL, MAX_PATH);
		set_var(&shell->vars, "PWD", pwd, 1);
		free(pwd);
	}
	else
		set_var(&shell->vars, "PWD", curpath, 1);
	free(curpath);
	return (0);
}

static int	cd_find_path(t_shell *shell, const char *dir, int option)
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
		if (!(pwd = ft_strdup(get_var_value(get_var(shell->exec_vars, "PWD")))))
			pwd = getcwd(NULL, MAX_PATH);
		if (pwd[ft_strlen(pwd) - 1] != '/')
			pwd = ft_strjoin_free(pwd, "/", 1);
		curpath = ft_strjoin_free(pwd, curpath, 3);
	}
	return (canonic_path(shell, curpath, dir, option));
}

int			builtin_cd(t_shell *shell, char **args)
{
	int			i;
	const char	*dir;
	int			option;

	if ((i = cd_parse_options(args, &option)) == -1)
		return (1);
	if (args[i] && args[i + 1])
		return (exit_error(NULL, "too many arguments"));
	if (args[i] && ft_strequ(args[i], "-"))
	{
		if (!(dir = get_var_value(get_var(shell->exec_vars, "OLDPWD"))))
			return (exit_error(NULL, "OLDPWD not set"));
		ft_dprintf(g_fd_output, "%s\n", dir);
		return (cd_find_path(shell, dir, option));
	}
	else if (args[i])
		return (cd_find_path(shell, args[i], option));
	if (!(dir = get_var_value(get_var(shell->exec_vars, "HOME"))))
		return (exit_error(NULL, "HOME not set"));
	return (cd_find_path(shell, dir, option));
}
