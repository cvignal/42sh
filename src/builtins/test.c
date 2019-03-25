/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 01:17:32 by fstadelw          #+#    #+#             */
/*   Updated: 2019/03/25 05:14:18 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"
#include "shell.h"
#include "test_bltn.h"

static int	test(char **args, bool if_bracket)
{
	(void)args;
	(void)if_bracket;
	return (0);
}

int			builtin_test(t_shell *shell, char **args)
{
	(void)shell;
	return (test(&args[1], ft_strequ(args[0], "[")));
}
