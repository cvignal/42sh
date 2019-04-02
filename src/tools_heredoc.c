/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 14:17:25 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/02 14:26:11 by cvignal          ###   ########.fr       */
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
	ft_bzero(&shell->exp_lexer.buffer, sizeof(shell->exp_lexer.buffer));
	ft_bzero(&shell->exp_lexer.var, sizeof(shell->exp_lexer.var));
	ret = expand(shell, heredoc->data, &error);
	if (error)
	{
		ft_dprintf(2, "%s: unable to allocate memory\n", EXEC_NAME);
		return (1);
	}
	write(fd[1], ret, ft_strlen(ret));
	free(ret);
	return (0);
}
