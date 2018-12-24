/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 20:19:01 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:43:31 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "21sh.h"

int	add_to_pipeline(t_pipeline *first, t_command *last)
{
	t_pipeline	*iter;
	t_pipeline	*new_pipeline;

	new_pipeline = create_pipeline(last);
	if (!new_pipeline)
		return (1);
	iter = first;
	while (iter->next)
		iter = iter->next;
	iter->next = new_pipeline;
	return (0);
}

t_pipeline	*create_pipeline(t_command *command)
{
	t_pipeline	*new_pipeline;

	new_pipeline = malloc(sizeof(*new_pipeline));
	if (!new_pipeline)
		return (NULL);
	new_pipeline->in_fd[STDIN_FILENO] = -1;
	new_pipeline->in_fd[STDOUT_FILENO] = -1;
	new_pipeline->out_fd[STDIN_FILENO] = -1;
	new_pipeline->out_fd[STDOUT_FILENO] = -1;
	new_pipeline->command = command;
	new_pipeline->next = NULL;
	return (new_pipeline);
}

void		delete_pipeline(t_pipeline *pipeline)
{
	t_pipeline	*tmp;

	while (pipeline)
	{
		tmp = pipeline;
		pipeline = pipeline->next;
		free_command(tmp->command);
		free(tmp);
	}
}

int		prepare_pipeline(t_pipeline *pipeline)
{
	t_pipeline	*last;
	int		fd[2];

	last = NULL;
	while (pipeline)
	{
		if (last)
		{
			if (pipe(fd))
				return (1);
			last->out_fd[0] = fd[0];
			last->out_fd[1] = fd[1];
			pipeline->in_fd[0] = fd[0];
			pipeline->in_fd[1] = fd[1];
		}
		last = pipeline;
		pipeline = pipeline->next;
	}
	return (0);
}

void		open_close_pipe(t_pipeline *pipeline, t_pipeline *current)
{
	while (pipeline)
	{
		if (pipeline != current && current->next != pipeline)
		{
			if (pipeline->in_fd[STDIN_FILENO] != -1)
				close(pipeline->in_fd[STDIN_FILENO]);
			if (pipeline->in_fd[STDOUT_FILENO] != -1)
				close(pipeline->in_fd[STDOUT_FILENO]);
		}
		pipeline = pipeline->next;
	}
	if (current->in_fd[STDOUT_FILENO] != -1)
		close(current->in_fd[STDOUT_FILENO]);
	if (current->out_fd[STDIN_FILENO] != -1)
		close(current->out_fd[STDIN_FILENO]);
	if (current->in_fd[STDIN_FILENO] != -1)
	{
		dup2(current->in_fd[STDIN_FILENO], STDIN_FILENO);
		close(current->in_fd[STDIN_FILENO]);
	}
	if (current->out_fd[STDOUT_FILENO] != -1)
	{
		dup2(current->out_fd[STDOUT_FILENO], STDOUT_FILENO);
		close(current->out_fd[STDOUT_FILENO]);
	}
}
