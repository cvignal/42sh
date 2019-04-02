/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_internal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:43:49 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/02 14:20:27 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

int	prepare_redirs(t_shell *shell, t_ast *instr, t_ast *root)
{
	t_redir	*redir;

	if (root && root != instr)
	{
		ft_memcpy(instr->old_fds, root->old_fds, sizeof(instr->old_fds));
		ft_memcpy(instr->fds, root->fds, sizeof(instr->fds));
	}
	redir = instr->redir_list;
	while (redir)
	{
		if (!redir->applied && redir->redir_act(shell, instr, redir))
		{
			ft_dprintf(2, "%s: redirection failed\n", EXEC_NAME);
			return (1);
		}
		redir->applied = 1;
		redir = redir->next;
	}
	if (instr->left)
		prepare_redirs(shell, instr->left, root);
	if (instr->right)
		prepare_redirs(shell, instr->right, root);
	return (0);
}

int	redir_l(t_shell *shell, t_ast *instr, t_redir *redir)
{
	int	fd;

	(void)shell;
	(void)instr;
	fd = open_file(shell, redir->target_value, O_RDONLY, 0);
	if (fd < 0)
		return (1);
	instr->fds[redir->in] = fd;
	redir->fd = fd;
	return (0);
}

int	redir_ll(t_shell *shell, t_ast *instr, t_redir *redir)
{
	t_heredoc	*heredoc;
	int			fd[2];
	int			ret;

	(void)instr;
	if (!(heredoc = alloc_heredoc()))
		return (1);
	if ((ret = read_heredoc(heredoc, redir)) == 1)
		return (heredoc_exit_error(heredoc));
	else if (ret == 2)
		shell->ctrlc = 1;
	if (pipe(fd))
		return (heredoc_exit_error(heredoc));
	if (heredoc->data)
		expand_heredoc(heredoc, shell, fd);
	close(fd[1]);
	redir->fd = fd[0];
	if (heredoc->data)
		free(heredoc->data);
	free(heredoc);
	return (0);
}

int	redir_r(t_shell *shell, t_ast *instr, t_redir *redir)
{
	int	fd;

	(void)instr;
	fd = open_file(shell, redir->target_value, O_WRONLY | O_CREAT | O_TRUNC,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (1);
	redir->fd = fd;
	return (0);
}

int	redir_rr(t_shell *shell, t_ast *instr, t_redir *redir)
{
	int	fd;

	(void)instr;
	(void)shell;
	fd = open_file(shell, redir->target_value, O_WRONLY | O_CREAT | O_APPEND,
			S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (1);
	redir->fd = fd;
	return (0);
}
