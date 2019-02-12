/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:48:47 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/12 21:46:15 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"
#include "expand.h"

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

static void	free_history(t_shell *shell)
{
	t_list	*list;
	t_list	*tmp;

	list = shell->history;
	while (list)
	{
		tmp = list->next;
		free(list->content);
		free(list);
		list = tmp;
	}
}

static void	free_shell_aux(t_shell *shell)
{
	t_fd	*fd;
	t_fd	*next_fd;

	lss_pop(&shell->lexer);
	pss_pop(&shell->parser);
	fd = shell->used_fd;
	while (fd)
	{
		next_fd = fd->next;
		free(fd);
		fd = next_fd;
	}
	free_token_list(shell->output);
	free_token_list(shell->current);
	if (shell->parser.ret)
	{
		shell->parser.ret->del(shell->parser.ret);
		shell->parser.ret = NULL;
	}
	exp_ss_pop(&shell->exp_lexer);
	free_history(shell);
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
	free_line(&shell->line);
	i = -1;
	if (shell->hash_table)
	{
		while (++i < HASH_TABLE_SIZE)
			if (shell->hash_table[i])
			{
				free(shell->hash_table[i]->path);
				free(shell->hash_table[i]->bin);
				free(shell->hash_table[i]);
			}
		free(shell->hash_table);
	}
	free_shell_aux(shell);
	reset_terminal_mode(shell);
}

int			init_shell(t_shell *shell, char **environ)
{
	if (init_lexer(&shell->lexer) || init_parser(&shell->parser)
			|| init_exp_lexer(&shell->exp_lexer))
		return (1);
	shell->hash_table = malloc(sizeof(*shell->hash_table) * HASH_TABLE_SIZE);
	if (!shell->hash_table)
		return (1);
	shell->used_fd = NULL;
	ft_bzero(shell->hash_table, sizeof(*shell->hash_table) * HASH_TABLE_SIZE);
	ft_bzero(&shell->line, sizeof(shell->line));
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
	shell->his_pos = -1;
	shell->ctrld = 0;
	shell->end_heredoc = 0;
	load_history(shell);
	return (0);
}
