/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 07:53:29 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/10 08:46:10 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# define PIPE_PARENT 0
# define PIPE_NODE 1

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
	TT_IFNOCD,
	TT_ELIF,
	TT_ELSE,
	TT_FI,
	TT_WHILE,
	TT_WHILECD,
	TT_WHILENOCD,
	TT_DO,
	TT_DONE,
	TT_STATEMENT,
	TT_OP,
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
t_ast_token				*alloc_ast_token(void *data, t_ttype type);
void					add_to_ast_token_list(t_ast_token **list,
		t_ast_token *node);
void					push_ast_token(t_ast_token **list, t_ast_token *node);
t_ast_token				*pop_ast_token(t_ast_token **list);

/*
** parser/utils.c
*/
void					shift_ast_token(t_parser *parser, t_ast_token *list,
		int del);
void					clean_last_end_token(t_parser *parser);

struct s_ast;
struct s_shell;
struct s_redir;
typedef int				(*t_exec)(struct s_shell *, struct s_ast *);
typedef void			(*t_free)(struct s_ast *);

typedef struct			s_ast
{
	t_ttype				type;
	t_exec				exec;
	t_free				del;
	int					pipes_in[2][2];
	int					pipes_out[2][2];
	int					old_fds[3];
	int					fds[3];
	void				*data;
	pid_t				pid;
	int					ret;
	struct s_redir		*redir_list;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef int				(*t_ast_act)(t_parser *, t_ast_token *);

typedef struct			s_ast_rule
{
	int					state_mask;
	t_ttype				types[3];
	size_t				len;
	t_ast_act			act;
}						t_ast_rule;

/*
** parser/rules.c
*/
int						rule_create_cmd(t_parser *parser, t_ast_token *list);
int						rule_add_to_cmd(t_parser *parser, t_ast_token *list);
int						rule_cmd_list(t_parser *parser, t_ast_token *list);
int						rule_create_end(t_parser *parser, t_ast_token *list);
int						rule_create_end_second(t_parser *parser,
		t_ast_token *list);

/*
** parser/rules_shift.c
*/
int						rule_shift_first(t_parser *parser, t_ast_token *list);
int						rule_shift_second(t_parser *parser, t_ast_token *list);

/*
** parser/rules_or.c
*/
int						rule_or(t_parser *parser, t_ast_token *list);
int						rule_and(t_parser *parser, t_ast_token *list);

/*
** parser/rules_redir.c
*/
int						rule_redir_l(t_parser *parser, t_ast_token *list);
int						rule_redir_ll(t_parser *parser, t_ast_token *list);
int						rule_redir_r(t_parser *parser, t_ast_token *list);
int						rule_redir_rr(t_parser *parser, t_ast_token *list);

/*
** parser/rule_redir_r_comp.c
*/
int						rule_redir_r_comp(t_parser *parser, t_ast_token *list);

/*
** parser/rule_redir_r_close.c
*/
int						rule_redir_r_close(t_parser *parser, t_ast_token *list);

/*
** parse/rules_redir_r_both.c
*/
int						rule_redir_r_both(t_parser *parser, t_ast_token *list);

/*
** parser/rules_pipeline.c
*/
int						rule_pipe(t_parser *parser, t_ast_token *list);

/*
** parser/rules_expr.c
*/
int						rule_create_expr(t_parser *parser, t_ast_token *list);
int						rule_add_to_expr(t_parser *parser, t_ast_token *list);
int						rule_close_expr(t_parser *parser, t_ast_token *list);
int						rule_make_expr(t_parser *parser, t_ast_token *list);

/*
** parser/rules_statement.c
*/
int						rule_create_statement(t_parser *parser,
		t_ast_token *list);

/*
** parser/rules_if.c
*/
int						rule_elif(t_parser *parser, t_ast_token *list);
int						rule_else(t_parser *parser, t_ast_token *list);
int						rule_close_if(t_parser *parser, t_ast_token *list);

/*
** parser/rules_if_nocd.c
*/
int						rule_create_if_nocd(t_parser *parser,
		t_ast_token *list);
int						rule_if_add_cd(t_parser *parser, t_ast_token *list);
int						rule_if_close_cd(t_parser *parser, t_ast_token *list);

/*
** parser/rules_while.c
*/
int						rule_create_while(t_parser *parser, t_ast_token *list);
int						rule_while_add_cd(t_parser *parser, t_ast_token *list);
int						rule_while_close_cd(t_parser *parser,
		t_ast_token *list);
int						rule_while_close(t_parser *parser, t_ast_token *list);

/*
** parser/rules_shunting_yard.c
*/
int						rule_send_to_shunting_yard(t_parser *parser,
		t_ast_token *list);

/*
** parser/ast.c
*/
t_ast					*alloc_ast(void *data, t_ttype type,
		t_exec exec, t_free del);
void					free_ast(t_ast *ast);

/*
** parser/shunting_yard.c
*/
void					shunting_yard(t_parser *parser);
t_ast					*queue_to_ast(t_pss *pss);
/*
** pasrser/parser_rules.c
*/
t_ast_act				get_rule(t_ast_token *tokens, int state);

/*
** parser/input_queue.c
*/
void					free_input_queue(t_ast_token *input);

#endif
