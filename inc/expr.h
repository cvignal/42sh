/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 12:37:43 by gchainet          #+#    #+#             */
/*   Updated: 2019/02/18 14:08:40 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPR_H
# define EXPR_H

struct s_shell;
typedef int			(*t_expr_exec)(struct s_shell *, char **);

typedef struct		s_expr
{
	char			**args;
	char			**args_value;
	size_t			len;
}					t_expr;

typedef struct		s_expr_desc
{
	char			*desc;
	t_expr_exec		exec;
}					t_expr_desc;

/*
** expr/expression.c
*/
int					exec_expr_internal(struct s_shell *shell, t_expr *expr);
int					add_to_expr(t_expr *expr, char *arg);
void				free_expr_internal(t_expr *expr);
t_expr				*alloc_expr(void);

/*
** expr/desc.c
*/
t_expr_exec			get_expr(const char *s);

int					expr_a(struct s_shell *shell, char **args);
int					expr_b(struct s_shell *shell, char **args);
int					expr_c(struct s_shell *shell, char **args);
int					expr_d(struct s_shell *shell, char **args);
int					expr_e(struct s_shell *shell, char **args);
int					expr_f(struct s_shell *shell, char **args);
int					expr_g(struct s_shell *shell, char **args);
int					expr_h(struct s_shell *shell, char **args);
int					expr_k(struct s_shell *shell, char **args);
int					expr_p(struct s_shell *shell, char **args);
int					expr_r(struct s_shell *shell, char **args);
int					expr_s(struct s_shell *shell, char **args);
int					expr_t(struct s_shell *shell, char **args);
int					expr_u(struct s_shell *shell, char **args);
int					expr_w(struct s_shell *shell, char **args);
int					expr_x(struct s_shell *shell, char **args);
int					expr_g_cap(struct s_shell *shell, char **args);
int					expr_l_cap(struct s_shell *shell, char **args);
int					expr_n_cap(struct s_shell *shell, char **args);
int					expr_o_cap(struct s_shell *shell, char **args);
int					expr_s_cap(struct s_shell *shell, char **args);
int					expr_ef(struct s_shell *shell, char **args);
int					expr_nt(struct s_shell *shell, char **args);
int					expr_ot(struct s_shell *shell, char **args);
int					expr_v(struct s_shell *shell, char **args);
int					expr_n(struct s_shell *shell, char **args);
int					expr_equal(struct s_shell *shell, char **args);
int					expr_not_equal(struct s_shell *shell, char **args);
int					expr_lower(struct s_shell *shell, char **args);
int					expr_sup(struct s_shell *shell, char **args);
int					expr_eq(struct s_shell *shell, char **args);
int					expr_ne(struct s_shell *shell, char **args);
int					expr_lt(struct s_shell *shell, char **args);
int					expr_le(struct s_shell *shell, char **args);
int					expr_gt(struct s_shell *shell, char **args);
int					expr_ge(struct s_shell *shell, char **args);

#endif
