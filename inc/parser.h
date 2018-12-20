/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 07:31:52 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/19 11:23:09 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <limits.h>

# define META_CHARS ";|&<>"

# define TOKEN_ALLOC_SIZE	128

struct s_shell;
struct s_ast;

typedef struct		s_token
{
	char			*data;
	size_t			alloc_size;
	size_t			len;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct		s_token_desc
{
	char			*str;
	int				type;
}					t_token_desc;

typedef enum		e_pstate
{
	PSTATE_NONE,
	PSTATE_WORD,
	NUMBER_PSTATE
}					t_pstate;

typedef enum		e_lstate
{
	LSTATE_NONE,
	LSTATE_WORD,
	LSTATE_META,
	NUMBER_LSTATE
}					t_lstate;

typedef enum		e_lexer_ret
{
	LEXER_RET_CUT,
	LEXER_RET_CREATE,
	LEXER_RET_CONT,
	LEXER_RET_ERROR
}					t_lexer_ret;

struct s_lexer;
typedef int			(*t_lexer_act)(struct s_lexer *, t_token *, char);

typedef struct		s_lexer
{
	t_lexer_act		lexer_actions[NUMBER_LSTATE][CHAR_MAX + 1];
	t_lstate		state;
}					t_lexer;

typedef struct		s_parser
{
	t_pstate		state;
}					t_parser;

/*
** parser/parser.c
*/
void				init_parser(t_parser *parser);
struct s_ast		*parse(struct s_shell *shell, t_token *tokens);

/*
** parser/token.c
*/
t_token				*alloc_token(void);
int					add_to_token(t_token *token, char c);
int					insert_into_token(t_token *token, char *data, int pos);
void				add_to_token_list(t_token **list, t_token *new_token);

/*
** parser/token_type.c
*/
int					set_token_type(t_token *token);

/*
** parser/lexer_act.c
*/
int					lexer_add(t_lexer *lexer, t_token *token, char c);
int					lexer_cut(t_lexer *lexer, t_token *token, char c);
int					lexer_create(t_lexer *lexer, t_token *token, char c);
int					lexer_pass(t_lexer *lexer, t_token *token, char c);
int					lexer_create_meta(t_lexer *lexer, t_token *token, char c);
int					lexer_add_meta(t_lexer *lexer, t_token *token, char c);

/*
** parser/lexer.c
*/
t_token				*lex(struct s_shell *shell, const char *line);
void				init_lexer(t_lexer *lexer);

#endif
