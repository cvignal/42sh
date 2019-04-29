/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:56:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/30 00:21:11 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <limits.h>

# include "libft.h"

# define DEFAULT_IFS " \n\t"

# define EXP_BUFFER_ALLOC_SIZE	128

# define EXP_LEXER_RET_CONT	(1 << 0)
# define EXP_LEXER_RET_ERROR (1 << 1)
# define EXP_LEXER_RET_OVER (1 << 2)

# define EXP_LEXER_MASK_ALL (~0)
# define EXP_LEXER_MASK_VARIABLE (1 << 0)
# define EXP_LEXER_MASK_HISTORY (1 << 1)
# define EXP_LEXER_MASK_QUOTE (1 << 2)
# define EXP_LEXER_MASK_HOME (1 << 3)
# define EXP_LEXER_MASK_ARI (1 << 4)
# define EXP_LEXER_MASK_FIELD_SPLITTING (1 << 5)

typedef enum			e_exp_state
{
	EXP_STATE_WORD,
	EXP_STATE_SQUOTE,
	EXP_STATE_DQUOTE,
	EXP_STATE_DOLLAR,
	EXP_STATE_VAR,
	EXP_STATE_ARI,
	EXP_STATE_ARI_PAREN,
	EXP_STATE_ESCAPED,
	NUMBER_EXP_STATE
}						t_exp_state;

typedef struct			s_exp_buff
{
	char				*buffer;
	unsigned int		pos;
	unsigned int		alloc_size;
}						t_exp_buff;

typedef struct			s_exp_ss
{
	t_exp_buff			buffer;
	t_exp_state			state;
	struct s_exp_ss		*next;
}						t_exp_ss;

struct s_exp_lexer;
struct s_shell;
struct s_redir;

typedef int				(*t_exp_lexer_f)(struct s_shell *, char, int);

typedef struct			s_exp_lexer
{
	t_exp_ss			*state;
	int					split;
	t_array				ret;
	const char			*ifs;
	t_exp_lexer_f		methods[NUMBER_EXP_STATE][CHAR_MAX + 1];
}						t_exp_lexer;

/*
** expansion/init.c
*/
int						init_exp_lexer(t_exp_lexer *exp_lexer);

/*
** expansion/exp_ss.c
*/
int						exp_ss_push(t_exp_lexer *lexer, t_exp_state state);
char					*exp_ss_pop(t_exp_lexer *lexer);

/*
** expansion/lexer.c
*/
struct s_command;
int						expand_params(struct s_shell *shell,
		struct s_command *command, int mask);
char					*expand_no_split(struct s_shell *shell, char *arg,
		int *error, int mask);
int						expand_redirs(struct s_shell *shell,
		struct s_redir *list, int mask);

/*
** expansion/home.c
*/

/*
** expansion/buffer.c
*/
int						add_char_to_exp_buff(t_exp_lexer *lexer, char c);
int						add_string_to_exp_buff(t_exp_lexer *lexer,
		const char *s);
int						exp_lexer_add_to_buff(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_pop_add_to_buff(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_add_to_var(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_cut_var(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_push_var(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_push_squote(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_push_dquote(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_pop_quote(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_push_escaped(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_push_dollar(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_set_var(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_dollar_fail(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_set_ari(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_pop_ari(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_pop_ari_paren(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_push_ari_paren(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_set_ari(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_error(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_over(struct s_shell *shell, char c
		, int mask);

/*
** expansion/expr.c
*/
struct s_expr;
int						expand_expr(struct s_shell *shell, struct s_expr *expr);

/*
** expansion/lexer_methods_hist.c
*/
int						exp_lexer_cut_hist(struct s_shell *shell, char c
		, int mask);
int						exp_lexer_push_hist(struct s_shell *shell, char c
		, int mask);

#endif
