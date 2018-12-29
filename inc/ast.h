/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 07:53:29 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/29 17:10:43 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "parser.h"

typedef enum			e_ttype
{
	TT_WORD,
	TT_PARTIAL,
	TT_CMD,
	TT_PIPELINE,
	TT_END,
	TT_OR,
	TT_AND,
	TT_BG,
	TT_REDIR_L,
	TT_REDIR_R_COMP,
	TT_REDIR_R_CLOSE,
	TT_REDIR_LL,
	TT_REDIR_R,
	TT_REDIR_R_BOTH,
	TT_REDIR_RR,
	TT_EXPR_OPEN,
	TT_EXPR_CLOSE,
	TT_EXPR_INCOMPLETE,
	TT_EXPR,
	TT_PIPE,
	TT_IF,
	TT_THEN,
	TT_IFCD,
	TT_ELIF,
	TT_ELSE,
	TT_FI,
	TT_STATEMENT,
	TT_OVER
}						t_ttype;

typedef struct			s_ast_token
{
	t_ttype				type;
	void				*data;
	struct s_ast_token	*next;
}						t_ast_token;

/*
** parser/ast_token.c
*/
t_ast_token				*alloc_ast_token(char *data, t_ttype type);
void					add_to_ast_token_list(t_ast_token **list,
		t_ast_token *node);

struct s_ast;
struct s_shell;
typedef int				(*t_exec)(struct s_shell *, struct s_ast *);
typedef void			(*t_free)(struct s_ast *);

typedef struct			s_ast
{
	t_ttype				type;
	t_exec				exec;
	t_free				del;
	void				*data;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef int				(*t_ast_act)(t_ast_token *);

typedef struct			s_ast_rule
{
	t_ttype				types[4];
	size_t				len;
	t_ast_act			act;
}						t_ast_rule;

/*
** parser/rules.c
*/
int						rule_create_cmd(t_ast_token *list);
int						rule_add_to_cmd(t_ast_token *list);
int						rule_create_end(t_ast_token *list);
int						rule_cmd_list(t_ast_token *list);

/*
** parser/rules_shift.c
*/
int						rule_shift_first(t_ast_token *list);
int						rule_shift_second(t_ast_token *list);

/*
** parser/rules_or.c
*/
int						rule_or(t_ast_token *list);
int						rule_and(t_ast_token *list);

/*
** parser/rules_redir.c
*/
int						rule_redir_l(t_ast_token *list);
int						rule_redir_ll(t_ast_token *list);
int						rule_redir_r(t_ast_token *list);
int						rule_redir_rr(t_ast_token *list);

/*
** parser/rule_redir_r_comp.c
*/
int						rule_redir_r_comp(t_ast_token *list);

/*
** parser/rule_redir_r_close.c
*/
int						rule_redir_r_close(t_ast_token *list);

/*
** parse/rules_redir_r_both.c
*/
int						rule_redir_r_both(t_ast_token *list);

/*
** parser/rules_pipeline.c
*/
int						rule_create_pipeline(t_ast_token *list);
int						rule_add_to_pipeline(t_ast_token *list);

/*
** parser/rules_expr.c
*/
int						rule_create_expr(t_ast_token *list);
int						rule_add_to_expr(t_ast_token *list);
int						rule_close_expr(t_ast_token *list);

/*
** parser/rules_statement.c
*/
int						rule_create_statement(t_ast_token *list);

/*
** parser/rules_if.c
*/
int						rule_create_if(t_ast_token *list);
int						rule_add_to_if(t_ast_token *list);
int						rule_create_elif(t_ast_token *list);
int						rule_create_else(t_ast_token *list);
int						rule_close_if(t_ast_token *list);

/*
** parser/ast.c
*/
t_ast					*alloc_ast(void *data, t_ttype type,
		t_exec exec, t_free del);
void					free_ast(t_ast *ast);
void					unshift_ast_token(t_ast_token **tokens);

/*
** pasrser/parser_rules.c
*/
t_ast_act				get_rule(t_ast_token *tokens);

/*
** parser/input_queue.c
*/
void					free_input_queue(t_ast_token *input);

#endif
