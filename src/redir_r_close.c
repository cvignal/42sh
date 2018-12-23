/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 19:41:37 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 19:44:20 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "21sh.h"

int	redir_r_close(t_shell *shell, t_redir *redir)
{
	(void)shell;
	close(redir->in);
	return (0);
}
