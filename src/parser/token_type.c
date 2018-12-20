/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 10:54:28 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/19 20:12:27 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "ast.h"
#include "libft.h"

static const t_token_desc	g_token_desc[] =
{
	{";", TT_END},
	{"|", TT_PIPE},
	{"||", TT_OR},
	{"&", TT_WORD},
	{"&&", TT_AND},
	{"<", TT_REDIR_L},
	{"<<", TT_REDIR_LL},
	{">", TT_REDIR_R},
	{">>", TT_REDIR_RR}
};

int	set_token_type(t_token *token)
{
	unsigned int	i;

	i = 0;
	while (i < sizeof(g_token_desc) / sizeof(*g_token_desc))
	{
		if (!ft_strcmp(token->data, g_token_desc[i].str))
		{
			token->type = g_token_desc[i].type;
			return (1);
		}
		++i;
	}
	return (0);
}
