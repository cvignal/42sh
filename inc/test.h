/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gchainet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 17:43:06 by gchainet          #+#    #+#             */
/*   Updated: 2019/06/24 18:55:58 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

typedef int				(*t_test_op)(t_shell *, char **);

typedef struct			s_test_desc
{
	char				*desc;
	t_test_op			test;
}						t_test_desc;

t_test_op				get_unary_op(char *s);
t_test_op				get_binary_op(char *s);

#endif
