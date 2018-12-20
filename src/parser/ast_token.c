/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 09:14:25 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/15 20:42:17 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"

t_ast_token	*alloc_ast_token(char *data, t_ttype type)
{
	t_ast_token	*new_token;

	if (!(new_token = malloc(sizeof(*new_token))))
		return (NULL);
	new_token->data = data;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void		add_to_ast_token_list(t_ast_token **list, t_ast_token *node)
{
	t_ast_token	*iter;

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

void		unshift_ast_token(t_ast_token **tokens)
{
	t_ast_token	*tmp;
	t_ast_token	*iter;

	tmp = NULL;
	if (!*tokens)
		return ;
	iter = *tokens;
	while (iter->next)
	{
		tmp = iter;
		iter = iter->next;
	}
	if (iter == *tokens)
		*tokens = NULL;
	free(iter);
	if (tmp)
		tmp->next = NULL;
}
