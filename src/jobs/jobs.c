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

	index = redir->type - TT_REDIR_L;
	return ft_strdup(chars[index]);
	/*
	if (redir->type == '<' || redir->type == '>')
		index = (redir->type == '>');
	else
		index = redir->type - TOK_DLESS + 2;
	str = ft_strcjoinf(ft_itoa(redir->redirected), ' ',
			ft_strdup(chars[index]));
	if (redir->dest.type == REDIR_FD)
		str = ft_strcjoinf(str, ' ', ft_itoa(redir->dest.val.fd));
	else if (redir->dest.type == REDIR_FILE)
		str = ft_strcjoinf(str, ' ', ft_strdup(redir->dest.val.file));
	else if (redir->dest.type == REDIR_CLOSE)
		str = ft_strcjoinf(str, ' ', ft_strdup("-"));
	return (str);
	*/
}

static char	*proc_to_string(t_ast *ast)
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
	(*p)->pid = ast->pid;
	(*p)->command = proc_to_string(ast);
	ast->job->last = *p;
	if (!ast->job->pgid)
		ast->job->pgid = ast->pid;
	setpgid(ast->pid, ast->job->pgid);
	return (0);
}
