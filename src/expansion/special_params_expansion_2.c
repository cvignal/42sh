/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_params_expansion_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marin </var/spool/mail/marin>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 17:23:42 by marin             #+#    #+#             */
/*   Updated: 2019/06/08 17:37:49 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "expand.h"
#include <unistd.h>

int	get_special_param_bang(t_shell *shell)
{
	(void) shell;
	return (0);
}

int	get_special_param_qmark(t_shell *shell)
{
	const char	*value;	

	value = get_var_value(get_var(shell->vars , "?"));
		return (add_string_to_exp_buff(&shell->exp_lexer, value));
}
