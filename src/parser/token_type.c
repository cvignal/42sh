/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:54:28 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/22 17:55:39 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"
#include "ast.h"
#include "libft.h"

static const t_token_desc	g_token_desc[] =
{
	{";", TT_END},
	{"|", TT_PIPE},
	{"||", TT_OR},
	{"&", TT_BG},
	{"&&", TT_AND},
	{"<", TT_REDIR_L},
	{"<<", TT_REDIR_LL},
	{">", TT_REDIR_R},
	{"d*>&d*", TT_REDIR_R},
	{">>", TT_REDIR_RR}
};

static const t_match_desc	g_match_desc[] =
{
	{'d', &ccmp_digit}
};

static t_char_cmp	get_token_cmp(char c)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_match_desc) / sizeof(*g_match_desc))
	{
		if (c == g_match_desc[i].desc)
			return (g_match_desc[i].func);
		++i;
	}
	return (&ccmp);
}

static int	match_pseudo_regex(const char *token, const char *desc)
{
	int				pos_token;
	int				pos_desc;
	t_char_cmp		cmp;
	int				match;

	pos_token = 0;
	pos_desc = 0;
	match = 1;
	while (match && token[pos_token] && desc[pos_desc])
	{
		match = 0;
		cmp = get_token_cmp(desc[pos_desc]);
		if (desc[pos_desc + 1] == '*')
		{
			while (cmp(token[pos_token], desc[pos_desc]))
			{
				match = 1;
				++pos_token;
			}
			++pos_desc;
		}
		else if (cmp(token[pos_token], desc[pos_desc]))
		{
			match = 1;
			++pos_token;
		}
		++pos_desc;
	}
	return (token[pos_token] || desc[pos_desc]);
}

int	get_token_type(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_token_desc) / sizeof(*g_token_desc))
	{
		if (!match_pseudo_regex(token->data, g_token_desc[i].str))
			return (g_token_desc[i].type);
		++i;
	}
	return (TT_WORD);
}
