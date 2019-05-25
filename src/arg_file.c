/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagrant </var/spool/mail/vagrant>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 21:34:02 by vagrant           #+#    #+#             */
/*   Updated: 2019/05/25 13:45:11 by marin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "shell.h"
#include <unistd.h>
#include "fill_line.h"
#include <sys/stat.h>
#include <fcntl.h>

void	set_shell_input_file(t_shell *shell, int ac, char **av)
{
	if ((shell->arg_file = malloc(sizeof(t_arg_file))) == NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		exit(127);
	}
	shell->arg_file->filename = av[0];
	shell->arg_file->argv = av;
	shell->arg_file->argc = ac;
	if (!access(shell->arg_file->filename, F_OK))
	{
		if (!access(shell->arg_file->filename, R_OK))
		{
			if ((shell->arg_file->fd = open(shell->arg_file->filename, O_RDONLY)) != -1)
				return;
			//TODO permission denied message	
			ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
			exit(127);
		}
		//TODO: file not found message 
		ft_dprintf(STDERR_FILENO, "%s: %s\n", EXEC_NAME, MEMORY_ERROR_MSG);
		exit(127);
	}
}

void	parse_args(t_shell *shell, int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac && *av[i] == '-')
		i++; // will deal with shell params later
	if (ac != i)
		set_shell_input_file(shell, ac - i, &av[i]);
}
int	read_from_file(t_shell *shell)
{
	char	*line;

	reset_terminal_mode(shell);
	shell->fd_op = 1;
	g_fd_output = 1;
	shell->ctrlc = 0;
	if (get_next_line(shell->arg_file->fd, &line) <= 0)
		return (1);
	shell->line.data = line;
	shell->line.len = ft_strlen(line);
	shell->history = NULL;
	return (0);
}
