/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_history_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 10:28:57 by cvignal           #+#    #+#             */
/*   Updated: 2019/03/12 12:06:05 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "shell.h"
#include "libft.h"
#include "fill_line.h"

int		open_history_file(t_shell *shell)
{
	char	*file;
	char	*home_dir;
	int		fd;
	int		flag;

	flag = 0;
	if (!(home_dir = get_env_value(shell, "HOME")))
	{
		if (!(home_dir = ft_strjoin("/Users/", getlogin())))
			return (-1);
		flag = 1;
	}
	if (!(file = ft_strjoin(home_dir, "/.shperso_history")))
		return (-1);
	fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	ft_strdel(&file);
	if (flag)
		free(home_dir);
	return (fd);
}
