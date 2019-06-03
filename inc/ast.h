/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 07:53:29 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/29 23:32:31 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# define PIPE_PARENT 0
# define PIPE_NODE 1

# include <sys/types.h>

# include "parser.h"

typedef enum			e_ttype
{
	TT_AND,
	TT_ARI,
	TT_ARI_ID,
	TT_ARI_NUMBER,
	TT_ARI_OP_AND,
	TT_ARI_OP_CMP_EQ,
	TT_ARI_OP_CMP_INF,
	TT_ARI_OP_CMP_INF_EQ,
	TT_ARI_OP_CMP_NOT_EQ,
	TT_ARI_OP_CMP_SUP,
	TT_ARI_OP_CMP_SUP_EQ,
	TT_ARI_OP_DIV,
	TT_ARI_OP_EQ,
	TT_ARI_OP_MOD,
	TT_ARI_OP_OR,
	TT_ARI_OP_PLUS,
	TT_ARI_OP_PLUS_PLUS,
	TT_ARI_OP_PROD,
	TT_ARI_OP_SUB,
	TT_ARI_OP_SUB_SUB,
	TT_ARI_OP_UPLUS,
	TT_ARI_OP_USUB,
	TT_ASSIGNEMENT,
	TT_BG,
	TT_CLOSE_PAR,
	TT_CMD,
	TT_DO,
	TT_DONE,
	TT_ELIF,
	TT_ELSE,
	TT_END,
	TT_END_UNARY,
	TT_EXPR,
	TT_EXPR_CLOSE,
	TT_EXPR_OPEN,
	TT_FI,
	TT_IF,
	TT_IFCD,
	TT_IFNOCD,
	TT_OP,
	TT_OPEN_PAR,
	TT_OR,
	TT_OVER,
	TT_PAR,
	TT_PARTIAL,
	TT_PIPE,
	TT_REDIR_L,
	TT_REDIR_L_CLOSE,
	TT_REDIR_L_COMP,
	TT_REDIR_LL,
	TT_REDIR_R,
	TT_REDIR_R_BOTH,
	TT_REDIR_R_CLOSE,
	TT_REDIR_R_COMP,
	TT_REDIR_RR,
	TT_REDIR_RW,
	TT_STATEMENT,
	TT_THEN,
	TT_WHILE,
	TT_WHILECD,
	TT_WHILENOCD,
	TT_WORD
}						t_ttype;

typedef enum			e_asso
{
	LEFT,
	RIGHT
}						t_asso;

typedef struct			s_op_prop
{
	t_ttype				type;
	int					arity;
	t_asso				asso;
	int					precedence;
}						t_op_prop;

/*
** parser/ast_token.c
*/
t_token					*alloc_ast_token(void *data, t_ttype type);
void					add_to_ast_token_list(t_token **list,
		t_token *node);
void					push_ast_token(t_token **list, t_token *node);
t_token					*pop_ast_token(t_token **list);
void					free_ast_token(t_token *token);

/*
** parser/utils.c
*/
void					shift_token(t_parser *parser, t_token *list,
		int del);
void					clean_last_end_token(t_parser *parser);

struct s_ast;
struct s_shell;
struct s_redir;
struct s_var;
typedef int				(*t_exec)(struct s_shell *, struct s_ast *);
typedef void			(*t_free)(struct s_ast *);

typedef struct			s_ast
{
	t_ttype				type;
	t_exec				exec;
	t_free				del;
	struct s_var		*assignements;
	int					rec_lvl;
	int					pipes_in[2][2];
	int					pipes_out[2][2];
	int					old_fds[10];
	int					fds[10];
	void				*data;
	pid_t				pid;
	int					ret;
	struct s_redir		*redir_list;
	struct s_ast		*left;
	struct s_ast		*right;
}						t_ast;

typedef int				(*t_ast_act)(t_parser *, t_token *);

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
int						rule_push_cmd(t_parser *parser, t_token *list);
int						rule_add_to_cmd(t_parser *parser, t_token *list);
int						rule_create_end(t_parser *parser, t_token *list);
int						rule_create_end_second(t_parser *parser,
		t_token *list);
int						rule_first_word(t_parser *parser, t_token *list);

/*
** parser/rules_shift.c
*/
int						rule_shift_first(t_parser *parser, t_token *list);
int						rule_shift_second(t_parser *parser, t_token *list);

/*
** parser/rules_or.c
*/
int						rule_or(t_parser *parser, t_token *list);
int						rule_and(t_parser *parser, t_token *list);

/*
** parser/rules_redir.c
*/
int						rule_redir_l(t_parser *parser, t_token *list);
int						rule_redir_ll(t_parser *parser, t_token *list);
int						rule_redir_r(t_parser *parser, t_token *list);
int						rule_redir_rr(t_parser *parser, t_token *list);

/*
** parser/rule_redir_r_comp.c
*/
int						rule_redir_r_comp(t_parser *parser, t_token *list);

/*
** parser/rule_redir_l_comp.c
*/
int						rule_redir_l_comp(t_parser *parser, t_token *list);

/*
** parser/rule_redir_r_close.c
*/
int						rule_redir_r_close(t_parser *parser, t_token *list);

/*
** parser/rule_redir_l_close.c
*/
int						rule_redir_l_close(t_parser *parser, t_token *list);

/*
** parser/rules_redir_r_both.c
*/
int						rule_redir_r_both(t_parser *parser, t_token *list);

/*
** parser/rules_redir_rw.c
*/
int						rule_redir_rw(t_parser *parser, t_token *list);

/*
** parser/rules_pipeline.c
*/
int						rule_pipe(t_parser *parser, t_token *list);

/*
** parser/rules_expr.c
*/
int						rule_create_expr(t_parser *parser, t_token *list);
int						rule_add_to_expr(t_parser *parser, t_token *list);
int						rule_close_expr(t_parser *parser, t_token *list);
int						rule_make_expr(t_parser *parser, t_token *list);

/*
** parser/rules_statement.c
*/
int						rule_create_statement(t_parser *parser,
		t_token *list);
int						rule_pop_cmd_statement(t_parser *parser,
		t_token *list);

/*
** parser/rules_if.c
*/
int						rule_elif(t_parser *parser, t_token *list);
int						rule_else(t_parser *parser, t_token *list);
int						rule_close_if(t_parser *parser, t_token *list);

/*
** parser/rules_if_nocd.c
*/
int						rule_create_if_nocd(t_parser *parser,
		t_token *list);
int						rule_if_add_cd(t_parser *parser, t_token *list);
int						rule_if_close_cd(t_parser *parser, t_token *list);

/*
** parser/rules_while.c
*/
int						rule_create_while(t_parser *parser, t_token *list);
int						rule_while_add_cd(t_parser *parser, t_token *list);
int						rule_while_close_cd(t_parser *parser,
		t_token *list);
int						rule_while_close(t_parser *parser, t_token *list);

/*
** parser/rules_shunting_yard.c
*/
int						rule_send_to_shunting_yard(t_parser *parser,
		t_token *list);

/*
** parser/rules_ari.c
*/
int						rule_create_ari_statement(t_parser *parser,
		t_token *list);
int						rule_ari_over(t_parser *parser, t_token *list);
int						rule_create_ari_id(t_parser *parser, t_token *list);

/*
** parser/rules_ari_op.c
*/
int						rule_ari_op(t_parser *parser, t_token *list);
int						rule_ari_paren(t_parser *parser, t_token *list);

/*
** parser/rules_ari_incrementation.c
*/
int						rule_ari_pre_plus_plus(t_parser *parser,
		t_token *list);
int						rule_ari_post_plus_plus(t_parser *parser,
		t_token *list);

/*
** parser/rules_ari_decrementation.c
*/
int						rule_ari_pre_sub_sub(t_parser *parser,
		t_token *list);
int						rule_ari_post_sub_sub(t_parser *parser,
		t_token *list);

/*
** parser/rules_ari_mangle.c
*/
int						rule_ari_pre_mangle(t_parser *parser,
		t_token *list);
int						rule_ari_post_mangle(t_parser *parser,
		t_token *list);

/*
** parser/rules_ari_usub.c
*/
int						rule_ari_create_usub(t_parser *parser,
		t_token *list);

/*
** parser/rules_syntax_error.c
*/
int						rule_syntax_error(t_parser *parser,
		t_token *list);

/*
** parser/rules_parenthesis.c
*/
int						rule_parenthesis(t_parser *parser, t_token *list);

/*
** parser/ast.c
*/
t_ast					*alloc_ast(void *data, t_ttype type,
		t_exec exec, t_free del);
void					free_ast(t_ast *ast);
void					set_rec_lvl(t_ast *ast, int rec_lvl);

/*
** parser/shunting_yard.c
*/
void					shunting_yard(t_parser *parser);
t_ast					*queue_to_ast(t_pss *pss);
/*
** pasrser/parser_rules.c
*/
t_ast_act				get_rule(t_token *tokens, int state);

/*
** parser/input_queue.c
*/
void					free_input_queue(t_token *input);

/*
** parser/op_prop.c
*/
const t_op_prop			*get_op_prop(t_ttype type);

#endif
