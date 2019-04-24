/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:54:28 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 09:43:43 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "parser.h"
#include "ast.h"
#include "libft.h"
#include "arithmetic.h"

static const t_token_desc	g_token_desc[] =\
{
	{";", TT_END},
	{"|", TT_PIPE},
	{"||", TT_OR},
	{"&", TT_BG},
	{"&&", TT_AND},
	{"(", TT_OPEN_PAR},
	{")", TT_CLOSE_PAR},
	{"d*<", TT_REDIR_L},
	{"d*<<", TT_REDIR_LL},
	{"d*>", TT_REDIR_R},
	{"&>", TT_REDIR_R_BOTH},
	{">&", TT_REDIR_R_BOTH},
	{"d*<>", TT_REDIR_RW},
	{"d*>&", TT_PARTIAL},
	{"d*>&-", TT_REDIR_R_CLOSE},
	{"d*>&d*", TT_REDIR_R_COMP},
	{"d*>>", TT_REDIR_RR}
};

static const t_match_desc	g_match_desc[] =\
{
	{'d', &ccmp_digit},
	{'.', &ccmp_all}
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

static int			match_plus(const char *token, char c, t_char_cmp cmp,
		int *match)
{
	int	pos_token;

	pos_token = 0;
	while (token[pos_token] && cmp(token[pos_token], c))
		++pos_token;
	if (pos_token)
		*match = 1;
	return (pos_token);
}

static int			match_star(const char *token, char c, t_char_cmp cmp,
		int *match)
{
	int	pos_token;

	pos_token = 0;
	*match = 1;
	while (token[pos_token] && cmp(token[pos_token], c))
		++pos_token;
	return (pos_token);
}

static int			match_pseudo_regex(const char *token, const char *desc)
{
	int				pos_t;
	int				pos_d;
	t_char_cmp		cmp;
	int				match;

	pos_t = 0;
	pos_d = 0;
	match = 1;
	while (match && token[pos_t] && desc[pos_d])
	{
		match = 0;
		cmp = get_token_cmp(desc[pos_d]);
		if (desc[pos_d + 1] == '*')
			pos_t += match_star(token + pos_t, desc[pos_d++], cmp, &match);
		else if (desc[pos_d + 1] == '+')
			pos_t += match_plus(token + pos_t, desc[pos_d++], cmp, &match);
		else if (cmp(token[pos_t], desc[pos_d]))
		{
			match = 1;
			++pos_t;
		}
		++pos_d;
	}
	return (!match || token[pos_t] || desc[pos_d]);
}

int					get_token_type(t_token *token, int state)
{
	unsigned int	i;

	i = 0;
	if (state == LSTATE_ARI_NONE || state == LSTATE_ARI_OP
			|| state == LSTATE_ARI_ID)
		return (get_arithmetic_token_type(token->data));
	if (token->type == TT_PAR)
		return (TT_PAR);
	while (i < sizeof(g_token_desc) / sizeof(*g_token_desc))
	{
		if (!match_pseudo_regex(token->data, g_token_desc[i].str))
			return (g_token_desc[i].type);
		++i;
	}
	return (TT_WORD);
}
