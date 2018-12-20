/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:29:12 by cvignal           #+#    #+#             */
/*   Updated: 2018/12/19 16:11:42 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

void	run_process(pid_t pid, char **args)
{
	pid_t	wpid;
	int		status;

	wpid = waitpid(pid, &status, WUNTRACED);
	while (!WIFEXITED(status) && !WIFSIGNALED(status))
		wpid = waitpid(pid, &status, WUNTRACED);
	check_segfault(args[0], status);
}

int		ft_execprocess(char **args, char **env)
{
	pid_t	pid;

	if (!add_path(args, env))
	{
		ft_printf("minishell: command not found: %s\n", args[0]);
		return (0);
	}
	else if (access(args[0], X_OK))
	{
		ft_printf("minishell: permission denied %s\n", args[0]);
		return (0);
	}
	ignore_signal();
	pid = fork();
	if (pid == 0)
	{
		enable_signal();
		execve(args[0], args, env);
	}
	else
		run_process(pid, args);
	return (1);
}

void	iterate_shlvl(char ***env)
{
	char	*shlvl;
	int		i;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strnequ((*env)[i], "SHLVL", 5))
		{
			shlvl = ft_ltoa_base(ft_atoi(ft_getenv(*env, "SHLVL")) + 1, 10);
			ft_strdel(&(*env)[i]);
			(*env)[i] = ft_strdup("SHLVL=");
			(*env)[i] = ft_strjoin_free((*env)[i], shlvl, 3);
		}
		i++;
	}
}

int		ft_launch(char **args, char ***env, char *line)
{
	if (*args && !builtin(args[0]))
		return (ft_execprocess(args, *env));
	else
		return (exec_builtin(args, env, line));
}

int		main(const int ac, const char **av, const char **env)
{
	char	*line;
//	char	**args;
	char	**my_env;

	(void)ac;
	(void)av;
	my_env = copy_env(env);
	iterate_shlvl(&my_env);
	while (42)
	{
		//disable_signal();
		ft_printf("%sMYSHELL%s%s$>%s ", "\e[1;36m",
				"\e[0m", "\e[1;31m", "\e[0m");
		line = fill_line();
		ft_printf("%s | len : %lu\n", line, ft_strlen(line));
	//	args = ft_strsplit(line, "\t ");
	//	args = ft_replace(args, my_env);
	//	ft_launch(args, &my_env, line);
	//	ft_strdel(&line);
	//	ft_deltab(&args);
	}
	return (0);
}
