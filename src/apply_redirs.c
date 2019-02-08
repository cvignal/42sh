/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/06 20:01:29 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/08 04:31:53 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "ast.h"

static t_redir_apply_desc	g_redir_apply_desc[] =\
{
	{TT_REDIR_R, &apply_redir_generic},
	{TT_REDIR_RR, &apply_redir_generic},
	{TT_REDIR_L, &apply_redir_generic},
	{TT_REDIR_LL, &apply_redir_generic},
	{TT_REDIR_R_CLOSE, &apply_redir_r_close},
	{TT_REDIR_R_COMP, &apply_redir_r_comp},
	{TT_REDIR_R_BOTH, &apply_redir_r_both}
};

int		apply_redirs(t_shell *shell, t_ast *instr)
{
	t_redir			*redir;
	unsigned int	i;

	(void)shell;
	redir = instr->redir_list;
	while (redir)
	{
		i = 0;
		while (i < sizeof(g_redir_apply_desc) / sizeof(*g_redir_apply_desc))
		{
			if (redir->type == g_redir_apply_desc[i].type)
			{
				if (g_redir_apply_desc[i].apply(redir))
					return (1);
			}
			++i;
		}
		redir = redir->next;
	}
	return (0);
}

int		apply_redir_generic(t_redir *redir)
{
	if (dup2(redir->fd, redir->in) == -1)
	{
		ft_dprintf(2, "%s: unable to create redirection\n", EXEC_NAME);
		return (1);
	}
	return (0);
}

int		apply_redir_r_close(t_redir *redir)
{
	if (close(redir->in))
	{
		ft_dprintf(2, "%s: unable to close file descriptor %d\n", EXEC_NAME, redir->fd);
		return (1);
	}
	return (0);
}

int		apply_redir_r_both(t_redir *redir)
{
	if (dup2(redir->fd, STDIN_FILENO) == -1
			|| dup2(redir->fd, STDERR_FILENO == -1))
	{
		ft_dprintf(2, "%s: unable to create redirection\n", EXEC_NAME);
		return (1);
	}
	return (0);
}

int		apply_redir_r_comp(t_redir *redir)
{
	if (dup2(redir->out, redir->in) == -1)
	{
		ft_dprintf(2, "%s: unable to create redirection\n", EXEC_NAME);
		return (1);
	}
	return (0);
}
