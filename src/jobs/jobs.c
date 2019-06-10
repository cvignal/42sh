/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrouard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 09:52:57 by agrouard          #+#    #+#             */
/*   Updated: 2018/12/12 09:54:33 by agrouard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jobs.h"
#include "shell.h"

#include <unistd.h>
#include <signal.h>

int			register_job(t_shell *shell, t_job *job)
{
	t_job	*j;

	if (!job->proc)
	{
		free_job(shell, job);
		return (0);
	}
	if (!(j = shell->jobs))
	{
		shell->jobs = job;
		job->index = 1;
	}
	else
	{
		while (j->next)
			j = j->next;
		j->next = job;
		job->index = j->index + 1;
	}
	if (!job->async)
		return (job_fg(shell, job, 0));
	job_bg(job, 0);
	return (0);
}

static char *redir_to_string(t_redir *redir)
{
	static char *chars[] = {"<", "<&-", "<&", "<<",
		">", ">&", ">&-", ">&", ">>", "<>"};
	int			index;
	char		*str;

	index = redir->type - TT_REDIR_L;
	str = ft_strjoin_free(ft_itoa(redir->in), chars[index], 1);
	if (redir->target)
		str = ft_strjoin_free(str, redir->target, 1);
	else if (redir->type == TT_REDIR_L_COMP ||
			redir->type == TT_REDIR_R_COMP)
		str = ft_strjoin_free(str, ft_itoa(redir->fd), 1 | 2);
	return (str);
}

static char	*ast_to_string(t_ast *ast)
{
	size_t		i;
	char		*str;
	t_command	*cmd;
	t_redir		*redir;

	i = 0;
	cmd = (t_command *)ast->data;
	str = ft_strdup(cmd->args[i]);
	while (++i < cmd->args_len)
		str = ft_strcjoin_free(str, ' ', cmd->args[i], 1);
	redir = ast->redir_list;
	while (redir)
	{
		str = ft_strcjoin_free(str, ' ', redir_to_string(redir), 1 | 2);
		redir = redir->next;		
	}
	return (str);
}

int			register_proc(t_ast *ast)
{
	t_proc	**p;

	p = &ast->job->proc;
	if (ast->job->last)
		p = &(ast->job->last)->next;
	if (!(*p = ft_memalloc(sizeof(t_proc))))
		return (1);
	ast->job->last = *p;
	if (!ast->job->pgid)
		ast->job->pgid = ast->pid;
	setpgid(ast->pid, ast->job->pgid);
	(*p)->pid = ast->pid;
	(*p)->name = ast_to_string(ast);
	return (0);
}
