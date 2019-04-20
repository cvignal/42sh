/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_msg.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 04:20:06 by fstadelw          #+#    #+#             */
/*   Updated: 2019/04/18 19:59:09 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_MSG_H
# define SIG_MSG_H

# include <signal.h>

/*
** used to match an Error message to it's value
*/
typedef struct	s_sig_msg
{
	pid_t		sig;
	const char	*msg;
	unsigned char		rtn;
}				t_sig_msg;

#endif
