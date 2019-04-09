/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:51:49 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/09 09:22:39 by gchainet         ###   ########.fr       */
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

static int	change_dir(t_shell *shell, char *dir)
{
	char	*cwd;

	if (!dir)
		return (1);
	if (!(cwd = getcwd(NULL, MAX_PATH)))
		return (1);
	if (chdir(dir))
	{
		free(cwd);
		return (exit_error_cd(dir));
	}
	set_var(shell, "OLDPWD", cwd, 1);
	free(cwd);
	cwd = getcwd(NULL, MAX_PATH);
	set_var(shell, "PWD", cwd, 1);
	free(cwd);
	return (0);
}

int			builtin_cd(t_shell *shell, char **args)
{
	size_t			arg_len;
	unsigned int	i;
	t_var			*var;

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
			if (!(var = get_var(shell, "OLDPWD")) || !var->len_value)
				return (exit_error(NULL, "OLDPWD not set"));
			ft_dprintf(g_fd_output, "%s\n", var->var + var->len_name + 1);
			return (change_dir(shell, var->var + var->len_name + 1));
		}
		else
			return (change_dir(shell, args[i]));
	}
	if (!(var = get_var(shell, "HOME")) || !var->len_value)
		return (exit_error(NULL, "HOME not set"));
	return (change_dir(shell, var->var + var->len_name + 1));
}
