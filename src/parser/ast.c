/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 08:26:16 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/01 15:36:06 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "ast.h"
#include "shell.h"

static void	set_pipes(t_ast *new_node)
{
	new_node->pipes_in[PIPE_PARENT][STDIN_FILENO] = -1;
	new_node->pipes_in[PIPE_PARENT][STDOUT_FILENO] = -1;
	new_node->pipes_out[PIPE_PARENT][STDIN_FILENO] = -1;
	new_node->pipes_out[PIPE_PARENT][STDOUT_FILENO] = -1;
	new_node->pipes_in[PIPE_NODE][STDIN_FILENO] = -1;
	new_node->pipes_in[PIPE_NODE][STDOUT_FILENO] = -1;
	new_node->pipes_out[PIPE_NODE][STDIN_FILENO] = -1;
	new_node->pipes_out[PIPE_NODE][STDOUT_FILENO] = -1;
}

static void	set_ast_fd(t_ast *new_node)
{
	unsigned int	i;

	i = 0;
	while (i < 10)
	{
		new_node->fds[i] = -1;
		new_node->old_fds[i] = -1;
		++i;
	}
	new_node->old_fds[STDIN_FILENO] = STDIN_FILENO;
	new_node->old_fds[STDOUT_FILENO] = STDOUT_FILENO;
	new_node->old_fds[STDERR_FILENO] = STDERR_FILENO;
}

t_ast		*alloc_ast(void *data, t_ttype type, t_exec exec, t_free del)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->data = data;
	new_node->type = type;
	new_node->exec = exec;
	new_node->del = del;
	new_node->pid = -1;
	new_node->ret = 0;
	new_node->redir_list = NULL;
	new_node->right = NULL;
	new_node->left = NULL;
	set_ast_fd(new_node);
	set_pipes(new_node);
	return (new_node);
}

void		free_ast(t_ast *ast)
{
	t_redir	*node;
	t_redir	*tmp;

	node = ast->redir_list;
	while (node)
	{
		tmp = node;
		node = node->next;
		if (tmp->target)
			free(tmp->target);
		if (tmp->target_value)
			free(tmp->target_value);
		free(tmp);
	}
	free(ast);
}
