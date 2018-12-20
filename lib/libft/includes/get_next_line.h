/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:16:08 by gchainet          #+#    #+#             */
/*   Updated: 2018/11/12 15:56:19 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE	256

typedef struct			s_gnl_buffer
{
	char				buffer[BUFF_SIZE];
	int					fd;
	int					buffer_pos;
	int					read_size;
	struct s_gnl_buffer	*next;
}						t_gnl_buffer;

int						get_next_line(const int fd, char **line);

#endif
