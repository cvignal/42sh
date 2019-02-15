/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 15:49:17 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/15 13:18:27 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

static int	is_over(t_ast *ast)
{
	if (ast)
	{
		if (ast->pid == -1)
			return (is_over(ast->left) && is_over(ast->right));
		return (0);
	}
	return (1);
}

static int	set_process_as_finished(t_ast *ast, pid_t pid, int status)
{
	if (ast)
	{
		if (ast->pid == pid)
		{
			ast->pid = -1;
			ast->ret = WEXITSTATUS(status);
			return (1);
		}
		else
		{
			if (!set_process_as_finished(ast->left, pid, status))
				set_process_as_finished(ast->right, pid, status);
		}
	}
	return (0);
}

static void	do_wait(t_ast *ast)
{
	int		status;
	pid_t	pid;

	if ((pid = waitpid(0, &status, 0)) > 0)
	{
		if (WIFEXITED(status) || WIFSIGNALED(status))
			set_process_as_finished(ast, pid, status);
	}
}

int			wait_loop(t_ast *ast)
{
	reset_terminal_mode(NULL);
	while (!is_over(ast))
		do_wait(ast);
	return (0);
}
