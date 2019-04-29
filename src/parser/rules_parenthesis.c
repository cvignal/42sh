/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_parenthesis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 09:24:03 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/27 23:13:00 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "ast.h"

static int	is_arithmetic(const char *token)
{
	size_t	len;

	len = ft_strlen(token);
	if (len >= 4)
	{
		if (token[0] == '(' && token[1] == '('
				&& token[len - 1] == ')' && token[len - 2] == ')')
			return (1);
	}
	return (0);
}

int			rule_parenthesis(t_parser *parser, t_token *list)
{
	(void)parser;
	if (is_arithmetic(list->data))
		list->type = TT_ARI;
	else
		list->type = TT_WORD;
	return (0);
}
