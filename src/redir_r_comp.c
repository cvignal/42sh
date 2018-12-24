/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_r_comp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 12:35:46 by gchainet          #+#    #+#             */
/*   Updated: 2018/12/23 18:50:00 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "21sh.h"

int	redir_r_comp(t_shell *shell, t_redir *redir)
{
	(void)shell;
	dup2(redir->out, redir->in);
	return (0);
}
