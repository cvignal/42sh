/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 07:44:20 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/09 09:23:26 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

static void	print_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
		ft_printf("%s\n", shell->env[i++]);
}

static int	exit_error(const char *msg)
{
	ft_dprintf(2, "%s: env: %s\n", EXEC_NAME, msg);
	return (-1);
}

static int	set_vars(t_shell *tmp_shell, int *i, char **args)
{
	char	**word_split;
	int		error;

	error = 0;
	while (args[*i] && ft_strchr(args[*i], '='))
	{
		if ((word_split = split_env_arg(args[*i])))
		{
			if (set_env_var(tmp_shell, word_split[0], word_split[1]))
			{
				error = 1;
				break ;
			}
			free(word_split[0]);
			free(word_split[1]);
			free(word_split);
		}
		else
			return (exit_error(MEMORY_ERROR_MSG));
		++(*i);
	}
	return (error ? exit_error(MEMORY_ERROR_MSG) : 0);
}

int			builtin_env(t_shell *shell, char **args)
{
	t_shell	tmp_shell;
	int		i;

	tmp_shell.vars = copy_env(shell->env);
	i = builtin_env_get_opts(args, &tmp_shell);
	if (i == -1)
		return (1);
	set_vars(&tmp_shell, &i, args);
	if (args[i])
		exec_from_char(shell, args + i, &tmp_shell);
	else if (tmp_shell.env)
		print_env(&tmp_shell);
	remove_env(&tmp_shell);
	return (0);
}
