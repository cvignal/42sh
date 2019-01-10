/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rules.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 07:56:33 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/10 06:28:28 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "parser.h"
#include "libft.h"

static const t_ast_rule g_rules[] =\
{
	{PS_WHILENOCD, {TT_STATEMENT, 0, 0}, 1, &rule_while_add_cd},
	{PS_WHILENOCD, {TT_DO, 0, 0}, 1, &rule_while_close_cd},
	{PS_WHILENOCD | PS_IFNOCD, {TT_OVER, 0, 0}, 1, &rule_shift_first},
	{PS_WHILENOCD | PS_IFNOCD, {TT_END, 0, 0}, 1, &rule_shift_first},
	{PS_WHILECD, {TT_DONE, 0, 0}, 1, &rule_while_close},
	{PS_WHILECD | PS_IFCD,
		{TT_STATEMENT, TT_OVER, 0}, 2, &rule_create_end_second},
	{PS_IFNOCD, {TT_STATEMENT, 0, 0}, 1, &rule_if_add_cd},
	{PS_IFNOCD, {TT_THEN, 0, 0}, 1, &rule_if_close_cd},
	{PS_IFCD, {TT_FI, 0, 0}, 1, &rule_close_if},
	{PS_IFCD, {TT_ELIF, 0, 0}, 1, &rule_elif},
	{PS_IFCD, {TT_ELSE, 0, 0}, 1, &rule_else},
	{PS_EXPR, {TT_WORD, 0, 0}, 1, &rule_make_expr},
	{PS_EXPR, {TT_EXPR, TT_WORD, 0}, 2, &rule_add_to_expr},
	{PS_EXPR, {TT_EXPR_CLOSE, 0, 0}, 1, &rule_close_expr},
	{PS_NONE, {TT_OVER, 0, 0}, 1, &rule_shift_first},
	{PS_NONE, {TT_WORD, 0, 0}, 1, &rule_create_cmd},
	{PS_NONE, {TT_CMD, TT_WORD, 0}, 2, &rule_add_to_cmd},
	{PS_NONE, {TT_STATEMENT, TT_REDIR_R, TT_WORD}, 3, &rule_redir_r},
	{PS_NONE, {TT_STATEMENT, TT_REDIR_R_BOTH, TT_WORD}, 3, &rule_redir_r_both},
	{PS_NONE, {TT_STATEMENT, TT_REDIR_RR, TT_WORD}, 3, &rule_redir_rr},
	{PS_NONE, {TT_STATEMENT, TT_REDIR_L, TT_WORD}, 3, &rule_redir_l},
	{PS_NONE, {TT_STATEMENT, TT_REDIR_LL, TT_WORD}, 3, &rule_redir_ll},
	{PS_NONE, {TT_STATEMENT, TT_REDIR_R_COMP, 0}, 2, &rule_redir_r_comp},
	{PS_NONE, {TT_STATEMENT, TT_REDIR_R_CLOSE, 0}, 2, &rule_redir_r_close},
	{PS_NONE | PS_EXPR, {TT_STATEMENT, 0, 0}, 1, &rule_send_to_shunting_yard},
	{PS_NONE | PS_EXPR, {TT_OP, 0, 0}, 1, &rule_send_to_shunting_yard},
	{PS_NONE, {TT_EXPR_OPEN, 0, 0}, 1, &rule_create_expr},
	{PS_NONE | PS_EXPR, {TT_EXPR, 0, 0}, 1, &rule_create_statement},
	{PS_NONE, {TT_CMD, 0, 0}, 1, &rule_create_statement},
	{PS_NONE, {TT_PIPE, 0, 0}, 1, &rule_pipe},
	{PS_NONE | PS_EXPR, {TT_OR, 0, 0}, 1, &rule_or},
	{PS_NONE | PS_EXPR, {TT_AND, 0, 0}, 1, &rule_and},
	{PS_NONE, {TT_END, TT_OVER, 0}, 2, &rule_shift_first},
	{PS_NONE, {TT_END, TT_END, 0}, 2, &rule_shift_first},
	{PS_NONE, {TT_END, 0, 0}, 1, &rule_create_end},
	{PS_NONE, {TT_OVER, TT_OVER, 0}, 2, &rule_shift_second},
	{PS_NONE, {TT_IF, 0, 0}, 1, &rule_create_if_nocd},
	{PS_NONE, {TT_WHILE, 0, 0}, 1, &rule_create_while}
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
		size_t len_tokens, int state)
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
		return (state & g_rules[rule_id].state_mask);
	}
	return (0);
}

t_ast_act		get_rule(t_ast_token *tokens, int state)
{
	size_t			len_tokens;
	unsigned int	rule;

	if (!(len_tokens = count_tokens(tokens)))
		return (NULL);
	rule = 0;
	while (rule < sizeof(g_rules) / sizeof(*g_rules))
	{
		if (is_target_rule(tokens, rule, len_tokens, state))
			return (g_rules[rule].act);
		++rule;
	}
	return (NULL);
}
