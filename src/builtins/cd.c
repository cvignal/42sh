/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:51:49 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/21 15:03:42 by gchainet         ###   ########.fr       */
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

static int	change_dir(t_shell *shell, char *dir)
{
	char	*cwd;

	if (!dir)
		return (1);
	cwd = getcwd(NULL, MAX_PATH);
	if (chdir(dir))
	{
		free(cwd);
		return (exit_error(dir, "no such file or directory"));
	}
	set_env_var(shell, "OLDPWD", cwd);
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
			return (change_dir(shell, dir));
		}
		else
			return (change_dir(shell, args[i]));
	}
	if (!(dir = get_env_value(shell, "HOME")))
		return (exit_error(NULL, "HOME not set"));
	return (change_dir(shell, dir));
}
