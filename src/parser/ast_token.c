/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:14:25 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/27 16:44:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "libft.h"

t_token	*alloc_ast_token(void *data, t_ttype type)
{
	t_token	*new_token;

	if (!(new_token = malloc(sizeof(*new_token))))
		return (NULL);
	new_token->data = data;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void		add_to_ast_token_list(t_token **list, t_token *node)
{
	t_token	*iter;

	if (!*list)
		*list = node;
	else
	{
		iter = *list;
		while (iter->next)
			iter = iter->next;
		iter->next = node;
	}
}

void		push_ast_token(t_token **list, t_token *node)
{
	node->next = *list;
	*list = node;
}

t_token		*pop_ast_token(t_token **list)
{
	t_token	*ret;

	ret = *list;
	if (ret)
	{
		*list = (*list)->next;
		ret->next = NULL;
	}
	return (ret);
}

void		free_ast_token(t_token *token)
{
	if (token->data)
		free(token->data);
	free(token);
}
