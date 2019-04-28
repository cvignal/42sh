/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:17:25 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/28 04:06:48 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

int	expand_heredoc(t_heredoc *heredoc, t_shell *shell, int fd[2])
{
	int		error;
	char	*ret;

	error = 0;
	ret = do_expand(shell, heredoc->data, &error, EXP_LEXER_MASK_VARIABLE);
	if (error)
	{
		ft_dprintf(2, "%s: unable to allocate memory\n", EXEC_NAME);
		return (1);
	}
	write(fd[1], ret, ft_strlen(ret));
	free(ret);
	return (0);
}
