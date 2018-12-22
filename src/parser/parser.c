/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:36:20 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/22 13:01:03 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "minishell.h"
#include "libft.h"
#include "ast.h"
#include "libft.h"

static int			reduce(t_ast_token *input_queue)
{
	t_ast_act		act;

	if ((act = get_rule(input_queue)))
	{
		if (act(input_queue))
			return (2);
		return (1);
	}
	return (0);
}

static t_ast_token	*lookup(t_token **tokens)
{
	t_ast_token	*input_queue;
	t_ast_token	*new_token;
	t_token		*tmp;

	input_queue = NULL;
	while ((tmp = *tokens))
	{
		if (!(new_token = alloc_ast_token(tmp->data, tmp->type)))
			return (NULL);
		add_to_ast_token_list(&input_queue, new_token);
		*tokens = (*tokens)->next;
		free(tmp);
	}
	return (input_queue);
}

static t_ast		*get_return(t_ast_token *input)
{
	t_ast			*ret;

	ret = NULL;
	if (input->type == TT_OVER)
	{
		free(input->data);
		free(input);
	}
	else if (input->type != TT_PIPELINE || input->next)
	{
		free_input_queue(input);
		ft_putstr_fd("minishell: syntax error\n", 2);
	}
	else
	{
		ret = input->data;
		free(input);
	}
	return (ret);
}

t_ast				*parse(t_shell *shell, t_token *tokens)
{
	t_ast_token	*input_queue;
	t_ast_token	*lookup_queue;
	int			did_reduce;

	(void)shell;
	if (!tokens)
		return (NULL);
	input_queue = lookup(&tokens);
	did_reduce = 1;
	while (did_reduce)
	{
		did_reduce = 0;
		lookup_queue = input_queue;
		while (lookup_queue)
		{
			if (reduce(lookup_queue) == 1)
				did_reduce = 1;
			else
				lookup_queue = lookup_queue->next;
		}
	}
	return (get_return(input_queue));
}
