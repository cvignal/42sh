/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:36:02 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/27 23:17:47 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "shell.h"
#include "libft.h"

static int		realloc_token(t_token *token)
{
	char	*new_data;

	new_data = ft_realloc(token->data, token->len,
			token->alloc_size + TOKEN_ALLOC_SIZE);
	if (!new_data)
		return (1);
	token->alloc_size += TOKEN_ALLOC_SIZE;
	token->data = new_data;
	return (0);
}

t_token			*alloc_token(void)
{
	t_token	*new_token;

	new_token = malloc(sizeof(*new_token));
	if (!new_token)
		return (NULL);
	new_token->data = malloc(sizeof(*new_token->data) * TOKEN_ALLOC_SIZE);
	if (!new_token->data)
	{
		free(new_token);
		return (NULL);
	}
	ft_bzero(new_token->data, TOKEN_ALLOC_SIZE);
	new_token->alloc_size = TOKEN_ALLOC_SIZE;
	new_token->len = 0;
	new_token->next = NULL;
	new_token->type = TT_WORD;
	return (new_token);
}

int				add_to_token(t_token *token, char c)
{
	if (token->len + 2 >= token->alloc_size)
	{
		if (realloc_token(token))
			return (1);
	}
	((char *)token->data)[token->len++] = c;
	return (0);
}

void			add_to_token_list(t_token **list, t_token *new_token)
{
	t_token		*iter;

	if (!*list)
		*list = new_token;
	else
	{
		iter = *list;
		while (iter->next)
			iter = iter->next;
		iter->next = new_token;
	}
}

int				insert_into_token(t_token *token, char *data, int pos)
{
	char		*tmp;
	int			pos_tmp;

	if (!(tmp = ft_strdup(token->data + pos + 1)))
		return (1);
	token->len = pos;
	while (*data)
		if (add_to_token(token, *data++))
			return (1);
	pos_tmp = 0;
	while (tmp[pos_tmp])
		if (add_to_token(token, tmp[pos_tmp++]))
			return (1);
	free(tmp);
	return (0);
}
