/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 11:36:21 by gchainet          #+#    #+#             */
/*   Updated: 2019/01/16 12:40:24 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "shell.h"
#include "libft.h"

static const t_redir_desc g_redir_desc[] =\
{
	{TT_REDIR_L, &redir_l, &redir_l_save, &redir_l_reset},
	{TT_REDIR_LL, &redir_ll, &redir_ll_save, &redir_ll_reset},
	{TT_REDIR_R, &redir_r, &redir_r_save, &redir_r_reset},
	{TT_REDIR_RR, &redir_rr, &redir_rr_save, &redir_rr_reset},
	{TT_REDIR_R_COMP, &redir_r_comp, &redir_r_comp_save, &redir_r_comp_reset},
	{TT_REDIR_R_CLOSE, &redir_r_close, &redir_r_close_save,
		&redir_r_close_reset},
	{TT_REDIR_R_BOTH, &redir_r_both, &redir_r_both_save, &redir_r_both_reset},

};

static const t_redir_desc	*get_redir_desc(int type)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_redir_desc) / sizeof(*g_redir_desc))
	{
		if (type == g_redir_desc[i].type)
			return (g_redir_desc + i);
		++i;
	}
	return (NULL);
}

void						add_to_redir_list(t_ast *instr, t_redir *redir)
{
	t_redir	*iter;

	iter = instr->redir_list;
	if (!iter)
		instr->redir_list = redir;
	else
	{
		while (iter->next)
			iter = iter->next;
		iter->next = redir;
	}
}

t_redir						*create_redir(t_ttype type, char *arg,
		t_redir_act act)
{
	t_redir				*new_redir;
	const t_redir_desc	*rd;

	new_redir = malloc(sizeof(*new_redir));
	if (!new_redir)
		return (NULL);
	new_redir->target = ft_strdup(arg);
	if (!new_redir->target)
	{
		free(new_redir);
		return (NULL);
	}
	new_redir->type = type;
	new_redir->next = NULL;
	new_redir->redir_act = act;
	if ((rd = get_redir_desc(type)))
	{
		new_redir->redir_act = rd->act;
		new_redir->reset = rd->reset;
		new_redir->save = rd->save;
	}
	return (new_redir);
}
