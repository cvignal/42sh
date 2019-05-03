/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 13:35:26 by gchainet          #+#    #+#             */
/*   Updated: 2019/05/02 01:19:52 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

static const char	*get_home_value(t_shell *shell, const char *target)
{
	struct passwd	*passwd;

	if (!target)
		return (get_var_value(get_var(shell->vars, "HOME")));
	else if ((passwd = getpwnam(target)))
		return (passwd->pw_dir);
	return (NULL);
}

int					exp_lexer_push_tilde(t_shell *shell, char c, int mask)
{
	(void)c;
	if (mask & EXP_LEXER_MASK_TILDE &&
			((!(mask & EXP_LEXER_MASK_NO_MULTI_TILDE)
			  && shell->exp_lexer.state->buffer.pos
			  && shell->exp_lexer.state->buffer.buffer\
			  [shell->exp_lexer.state->buffer.pos - 1] == ':')
			 || (!shell->exp_lexer.ret.length
				 && !shell->exp_lexer.state->buffer.pos)))
	{
		if (exp_ss_push(&shell->exp_lexer, EXP_STATE_TILDE))
			return (EXP_LEXER_RET_ERROR);
	}
	else if (add_char_to_exp_buff(&shell->exp_lexer, c))
		return (EXP_LEXER_RET_ERROR);
	return (EXP_LEXER_RET_CONT);
}

int					exp_lexer_pop_tilde(t_shell *shell, char c, int mask)
{
	char			*buffer;
	const char		*home;

	(void)c;
	(void)mask;
	buffer = exp_ss_pop(&shell->exp_lexer);
	home = get_home_value(shell, buffer);
	if (home)
	{
		if (add_string_to_exp_buff(&shell->exp_lexer, home))
			return (EXP_LEXER_RET_ERROR);
	}
	else
	{
		if (add_char_to_exp_buff(&shell->exp_lexer, '~'))
			return (EXP_LEXER_RET_ERROR);
		if (add_string_to_exp_buff(&shell->exp_lexer, buffer))
			return (EXP_LEXER_RET_ERROR);
	}
	free(buffer);
	return (0);
}
