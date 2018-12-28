/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyword.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 12:24:56 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/26 12:30:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "parser.h"
#include "libft.h"

static const t_token_desc	g_keywords[] =
{
	{"[[", TT_EXPR_OPEN},
	{"]]", TT_EXPR_CLOSE}
};

int	keyword_type(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_keywords) / sizeof(*g_keywords))
	{
		if (!ft_strcmp(g_keywords[i].str, token->data))
			return (g_keywords[i].type);
		++i;
	}
	return (TT_WORD);
}
