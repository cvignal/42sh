/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 07:56:33 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/24 10:48:32 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"
#include "libft.h"

static const t_ast_rule g_rules[] =
{
	{{TT_WORD, 0, 0}, 1, &rule_create_cmd},
	{{TT_CMD, TT_WORD, 0}, 2, &rule_add_to_cmd},
	{{TT_CMD, TT_REDIR_R, TT_WORD}, 3, &rule_redir_r},
	{{TT_CMD, TT_REDIR_R_BOTH, TT_WORD}, 3, &rule_redir_r_both},
	{{TT_CMD, TT_REDIR_RR, TT_WORD}, 3, &rule_redir_rr},
	{{TT_CMD, TT_REDIR_L, TT_WORD}, 3, &rule_redir_l},
	{{TT_CMD, TT_REDIR_LL, TT_WORD}, 3, &rule_redir_ll},
	{{TT_CMD, TT_REDIR_R_COMP, 0}, 2, &rule_redir_r_comp},
	{{TT_CMD, TT_REDIR_R_CLOSE, 0}, 2, &rule_redir_r_close},
	{{TT_CMD, 0, 0}, 1, &rule_create_pipeline},
	{{TT_PIPELINE, TT_OVER, 0}, 2, &rule_shift_second},
	{{TT_PIPELINE, TT_OR, TT_PIPELINE}, 3, &rule_or},
	{{TT_PIPELINE, TT_AND, TT_PIPELINE}, 3, &rule_and},
	{{TT_PIPELINE, TT_END, TT_PIPELINE}, 3, &rule_create_end},
	{{TT_PIPELINE, TT_PIPE, TT_PIPELINE}, 3, &rule_add_to_pipeline},
	{{TT_END, TT_OVER, 0}, 2, &rule_shift_first},
	{{TT_END, TT_END, 0}, 2, &rule_shift_second}
};

static size_t	count_tokens(t_ast_token *tokens)
{
	size_t		size;

	size = 0;
	while (tokens)
	{
		++size;
		tokens = tokens->next;
	}
	return (size);
}

static int		is_target_rule(t_ast_token *token, unsigned int rule_id,
		size_t len_tokens)
{
	unsigned int	i;

	i = 0;
	if (g_rules[rule_id].len <= len_tokens)
	{
		while (i < g_rules[rule_id].len)
		{
			if (token->type != g_rules[rule_id].types[i])
				return (0);
			token = token->next;
			++i;
		}
		return (1);
	}
	return (0);
}

t_ast_act		get_rule(t_ast_token *tokens)
{
	size_t			len_tokens;
	unsigned int	rule;

	if (!(len_tokens = count_tokens(tokens)))
		return (NULL);
	rule = 0;
	while (rule < sizeof(g_rules) / sizeof(*g_rules))
	{
		if (is_target_rule(tokens, rule, len_tokens))
			return (g_rules[rule].act);
		++rule;
	}
	return (NULL);
}
