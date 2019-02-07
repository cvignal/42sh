/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:51:49 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/07 10:48:29 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

#include "shell.h"
#include "libft.h"

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

static int	change_dir(t_shell *shell, char *dir)
{
	char	*cwd;

	if (!dir)
		return (1);
	cwd = getcwd(NULL, MAX_PATH);
	if (chdir(dir))
	{
		free(cwd);
		return (exit_error_cd(dir));
	}
	set_env_var(shell, "OLDPWD", cwd);
	free(cwd);
	cwd = getcwd(NULL, MAX_PATH);
	set_env_var(shell, "PWD", cwd);
	free(cwd);
	return (0);
}

int			builtin_cd(t_shell *shell, char **args)
{
	size_t			arg_len;
	unsigned int	i;
	char			*dir;

	arg_len = 0;
	while (args[arg_len])
		++arg_len;
	if (arg_len > 3)
		return (exit_error(NULL, "too many arguments"));
	i = 1;
	while (i < arg_len)
	{
		if (!ft_strcmp(args[i], "-"))
		{
			if (!(dir = get_env_value(shell, "OLDPWD")))
				return (exit_error(NULL, "OLDPWD not set"));
			ft_printf("%s\n", dir);
			return (change_dir(shell, dir));
		}
		else
			return (change_dir(shell, args[i]));
	}
	if (!(dir = get_env_value(shell, "HOME")))
		return (exit_error(NULL, "HOME not set"));
	return (change_dir(shell, dir));
}
