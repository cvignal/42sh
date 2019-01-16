/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_reset_spec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 12:40:35 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/16 12:42:37 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	redir_r_comp_reset(struct s_redir *redir, t_ast *instr)
{
	(void)redir;
	(void)instr;
	return (0);
}

int	redir_r_both_reset(struct s_redir *redir, t_ast *instr)
{
	(void)redir;
	(void)instr;
	return (0);
}

int	redir_r_close_reset(struct s_redir *redir, t_ast *instr)
{
	(void)redir;
	(void)instr;
	return (0);
}
