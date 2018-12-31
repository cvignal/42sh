/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 07:46:37 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/31 17:10:05 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "21sh.h"
#include "ast.h"

static void	close_all_pipes(t_pipeline *pipeline)
{
	while (pipeline)
	{
		if (pipeline->in_fd[STDOUT_FILENO] != -1)
			close(pipeline->in_fd[STDOUT_FILENO]);
		if (pipeline->in_fd[STDIN_FILENO] != -1)
			close(pipeline->in_fd[STDIN_FILENO]);
		pipeline = pipeline->next;
	}
}

int			exec_pipeline(t_shell *shell, t_ast *ast)
{
	t_pipeline	*pipeline;

	(void)shell;
	pipeline = ast->data;
	if (prepare_pipeline(pipeline))
		return (1);
	while (pipeline)
	{
		if (exec(shell, ast->data, pipeline))
			return (1);
		pipeline = pipeline->next;
	}
	close_all_pipes(ast->data);
	return (wait_loop(ast->data));
}

void		free_pipeline(t_ast *ast)
{
	delete_pipeline(ast->data);
	free(ast);
}
