/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:17:25 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/30 01:31:33 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "shell.h"
#include "expand.h"
#include "libft.h"

int	expand_heredoc(t_heredoc *heredoc, t_shell *shell, int fd[2],
		const char *target)
{
	int		error;
	char	*ret;

	error = 0;
	if (!ft_strchr(target, '\'') && !ft_strchr(target, '\\')
			&& !ft_strchr(target, '"'))
		ret = expand_no_split(shell, heredoc->data, &error,
				EXP_LEXER_MASK_VARIABLE);
	else
		ret = NULL;
	if (error)
	{
		ft_dprintf(2, "%s: unable to allocate memory\n", EXEC_NAME);
		return (1);
	}
	if (ret)
	{
		write(fd[1], ret, ft_strlen(ret));
		free(ret);
	}
	else
		write(fd[1], heredoc->data, ft_strlen(heredoc->data));
	return (0);
}
