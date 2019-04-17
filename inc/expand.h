/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 13:56:50 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/12 21:37:03 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <limits.h>

# define EXP_BUFFER_ALLOC_SIZE	128

# define EXP_LEXER_RET_CONT	(1 << 0)
# define EXP_LEXER_RET_ERROR (1 << 1)

# define EXP_LEXER_MASK_ALL (~0)
# define EXP_LEXER_MASK_VARIABLE (1 << 0)
# define EXP_LEXER_MASK_HISTORY (1 << 1)
# define EXP_LEXER_MASK_QUOTE (1 << 2)
# define EXP_LEXER_MASK_HOME (1 << 3)

typedef enum			e_exp_state
{
	EXP_STATE_WORD,
	EXP_STATE_SQUOTE,
	EXP_STATE_DQUOTE,
	EXP_STATE_VAR,
	EXP_STATE_HIST,
	NUMBER_EXP_STATE
}						t_exp_state;

typedef struct			s_exp_ss
{
	t_exp_state			state;
	struct s_exp_ss		*next;
}						t_exp_ss;

typedef struct			s_exp_buff
{
	char				*buffer;
	unsigned int		pos;
	unsigned int		alloc_size;
}						t_exp_buff;

struct s_exp_lexer;
struct s_shell;
struct s_redir;

typedef int				(*t_exp_lexer_f)(struct s_shell *, char, int);

typedef struct			s_exp_lexer
{
	t_exp_buff			buffer;
	t_exp_buff			var;
	t_exp_ss			*state;
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
void					exp_ss_pop(t_exp_lexer *lexer);

/*
** expansion/lexer.c
*/
struct s_command;
int						expand_params(struct s_shell *shell,
		struct s_command *command, int mask);
char					*expand(struct s_shell *shell, char *arg, int *error,
		int mask);
int						expand_redirs(struct s_shell *shell,
		struct s_redir *list, int mask);

/*
** expansion/home.c
*/
int						expand_home(struct s_shell *shell, int *error, int mask);

/*
** expansion/buffer.c
*/
int						add_to_exp_buff(t_exp_buff *buffer, char c);
int						exp_lexer_add_to_buff(struct s_shell *shell, char c, int mask);
int						exp_lexer_add_to_var(struct s_shell *shell, char c, int mask);
int						exp_lexer_cut_var(struct s_shell *shell, char c, int mask);
int						exp_lexer_push_var(struct s_shell *shell, char c, int mask);
int						exp_lexer_push_squote(struct s_shell *shell, char c, int mask);
int						exp_lexer_push_dquote(struct s_shell *shell, char c, int mask);
int						exp_lexer_pop_quote(struct s_shell *shell, char c, int mask);

/*
** expansion/expr.c
*/
struct s_expr;
int					expand_expr(struct s_shell *shell, struct s_expr *expr);

/*
** expansion/lexer_methods_hist.c
*/
int						exp_lexer_cut_hist(struct s_shell *shell, char c, int mask);
int						exp_lexer_push_hist(struct s_shell *shell, char c, int mask);

#endif
