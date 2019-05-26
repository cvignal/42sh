/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_methods_special_params.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 14:57:18 by marin             #+#    #+#             */
/*   Updated: 2019/05/25 15:09:56 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"

int	exp_lexer_set_special_param(struct s_shell *shell, char c, int mask)
{

}

int	exp_lexer_cut_special_param(struct s_shell *shell, char c, int mask)
{
	char	*name;

	name = exp_ss_pop(&shell->exp_lexer);

}
