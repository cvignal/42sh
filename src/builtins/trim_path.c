/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:09:04 by cvignal           #+#    #+#             */
/*   Updated: 2019/04/24 16:18:13 by cvignal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static int		loop_trim(char *curpath, int top, int i, int j)
{
	while (curpath[++i] != '\0')
	{
		curpath[++top] = curpath[i];
		if (top >= 1 && curpath[top - 1] == '/' && curpath[top] == '.'
				&& (curpath[i + 1] == '/' || curpath[i + 1] == '\0'))
			top -= 2;
		else if (top >= 2 && curpath[top - 2] == '/' && curpath[top - 1]
				== '.' && curpath[top] == '.' && (curpath[i + 1]
					== '/' || curpath[i + 1] == '\0'))
		{
			j = top - 3;
			while (--j >= 0)
				if (curpath[j] == '/')
					break ;
			if (j < 0)
				top = -1;
			else
				top = j - 1;
		}
		else if (curpath[top] == '/' && curpath[i + 1] == '/')
			--top;
	}
	return (top);
}

int				canonic_path(t_shell *shell, char *curpath, char *dir
		, int option)
{
	int top;
	int i;
	int j;

	top = -1;
	i = -1;
	j = 0;
	top = loop_trim(curpath, top, i, j);
	if (top > 0)
	{
		if (curpath[top] == '/')
			curpath[top] = '\0';
		else
			curpath[top + 1] = '\0';
	}
	else if (top == 0)
		curpath[top + 1] = '\0';
	else
	{
		curpath[0] = '/';
		curpath[1] = '\0';
	}
	return (change_dir(shell, curpath, dir, option));
}
