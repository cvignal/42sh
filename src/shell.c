/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:48:47 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 19:01:33 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "21sh.h"
#include "libft.h"
#include "fill_line.h"

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
	if (shell->line)
		free(shell->line);
	reset_terminal_mode();
}

int			init_shell(t_shell *shell, char **environ)
{
	struct sigaction	sa;

	if (init_lexer(&shell->lexer))
		return (1);
	shell->line = NULL;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = &signal_sigint;
	sigaction(SIGINT, &sa, NULL);
	if (!(shell->env = copy_env(environ)))
	{
		ft_dprintf(2, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		return (1);
	}
	if (increment_shlvl(shell))
	{
		ft_dprintf(2, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		remove_env(shell);
		return (1);
	}
	raw_terminal_mode();
	return (0);
}
