/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 17:07:12 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/23 12:37:02 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

int					init_parser(t_parser *parser)
{
	ft_bzero(parser, sizeof(*parser));
	parser->ret_status = PARSER_COMPLETE;
	return (pss_push(parser, PS_NONE));
}
