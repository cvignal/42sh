/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 21:32:36 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/13 06:35:20 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETIC_H
# define ARITHMETIC_H

# include "ast.h"

typedef struct	s_ari_op_desc
{
	char		*desc;
	int			type;
	int			(*exec)(struct s_shell *, t_ast *);
	void		(*del)(t_ast *);
}				t_ari_op_desc;

typedef struct	s_ari_parser
{
	t_token	*output;
	t_token	*input_queue;
}				t_ari_parser;

struct s_shell;

int				alexer_input_error(struct s_shell *shell, t_token *current,
		char c);
int				alexer_create(struct s_shell *shell, t_token *current, char c);
int				alexer_cut(struct s_shell *shell, t_token *current, char c);
int				alexer_add(struct s_shell *shell, t_token *current, char c);
int				alexer_try_op(struct s_shell *shell, t_token *current, char c);

int				alexer_pop_paren(struct s_shell *shell, t_token *current,
		char c);
int				alexer_push_paren(struct s_shell *shell, t_token *current,
		char c);
int				alexer_count_paren(struct s_shell *shell, t_token *current,
		char c);

int				is_operator_char(char c);
int				get_arithmetic_token_type(const char *s);
int				get_arithmetic_desc(int type, t_ari_op_desc *dest);

int				init_arithmetic_lexer(t_lexer *lexer);

void			set_unary(t_token *list);

#endif
