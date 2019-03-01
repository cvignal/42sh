/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyword.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 12:24:56 by gchainet          #+#    #+#             */
/*   Updated: 2019/03/01 10:18:22 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "parser.h"
#include "libft.h"

static const t_token_desc	g_keywords[] =\
{
	{"[[", TT_EXPR_OPEN},
	{"]]", TT_EXPR_CLOSE},
	{"if", TT_IF},
	{"then", TT_THEN},
	{"elif", TT_ELIF},
	{"else", TT_ELSE},
	{"fi", TT_FI},
	{"while", TT_WHILE},
	{"do", TT_DO},
	{"done", TT_DONE}
};

int	keyword_type(const char *s)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_keywords) / sizeof(*g_keywords))
	{
		if (!ft_strcmp(g_keywords[i].str, s))
			return (g_keywords[i].type);
		++i;
	}
	return (TT_WORD);
}

int	is_a_keyword(const char *s)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_keywords) / sizeof(*g_keywords))
	{
		if (!ft_strcmp(g_keywords[i].str, s))
			return (1);
		++i;
	}
	return (0);
}
