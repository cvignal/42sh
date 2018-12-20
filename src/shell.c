/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:48:47 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/20 15:17:54 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "minishell.h"
#include "libft.h"

static int	increment_shlvl(t_shell *shell)
{
	char	*new_value;
	char	*shlvl;
	int		old_value;

	if ((shlvl = get_env_value(shell, "SHLVL")))
		old_value = ft_atoi(shlvl);
	else
		old_value = 0;
	if (!(new_value = ft_ltoa_base(old_value + 1, 10)))
		return (1);
	set_env_var(shell, "SHLVL", new_value);
	free(new_value);
	return (0);
}

void		free_shell(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->env)
	{
		while (shell->env[i])
			free(shell->env[i++]);
		free(shell->env);
	}
}

int			init_shell(t_shell *shell, char **environ)
{
	struct sigaction	sa;

	init_parser(&shell->parser);
	init_lexer(&shell->lexer);
	shell->line = NULL;
        ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &signal_sigint;
	sigaction(SIGINT, &sa, NULL);
	if (!(shell->env = copy_env(environ)))
	{
		ft_putstr_fd("minishell: unable to allocate memory\n", 2);
		return (1);
	}
	if (increment_shlvl(shell))
	{
		ft_putstr_fd("minishell: unable to allocate memory\n", 2);
		remove_env(shell);
		return (1);
	}
	return (0);
}
