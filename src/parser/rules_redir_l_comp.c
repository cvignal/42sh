/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_redir_l_comp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 11:05:09 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/24 11:17:35 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "ast.h"
#include "shell.h"
#include "libft.h"

int				rule_redir_l_comp(t_parser *parser, t_token *list)
{
	(void)list;
	if (create_redir_comp_generic(parser, TT_REDIR_L_COMP, &redir_l_comp))
		return (1);
	return (0);
}
