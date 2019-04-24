/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:50:02 by gchainet          #+#    #+#             */
/*   Updated: 2019/04/23 11:50:37 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	rule_syntax_error(t_parser *parser, t_token *list)
{
	(void)parser;
	(void)list;
	return (1);
}
