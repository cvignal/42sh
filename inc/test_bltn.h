/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bltn.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstadelw <fstadelw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 04:37:59 by fstadelw          #+#    #+#             */
/*   Updated: 2019/03/25 05:14:55 by fstadelw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_BLTN_H
# define TEST_BLTN_H

/*
** $$$$$$$$$$$$$$$$$$> help test <$$$$$$$$$$$$$$$$$$$
**
** test: test [expr]
**     Exits with a status of 0 (true) or 1 (false) depending on
**     the evaluation of EXPR.  Expressions may be unary or binary.  Unary
**     expressions are often used to examine the status of a file.  There
**     are string operators as well, and numeric comparison operators.
**
**     File operators:
**
**         -a FILE        True if file exists.
**         -b FILE        True if file is block special.
**         -c FILE        True if file is character special.
**         -d FILE        True if file is a directory.
**         -e FILE        True if file exists.
**         -f FILE        True if file exists and is a regular file.
**         -g FILE        True if file is set-group-id.
**         -h FILE        True if file is a symbolic link.
**         -L FILE        True if file is a symbolic link.
**         -k FILE        True if file has its `sticky' bit set.
**         -p FILE        True if file is a named pipe.
**         -r FILE        True if file is readable by you.
**         -s FILE        True if file exists and is not empty.
**         -S FILE        True if file is a socket.
**         -t FD          True if FD is opened on a terminal.
**         -u FILE        True if the file is set-user-id.
**         -w FILE        True if the file is writable by you.
**         -x FILE        True if the file is executable by you.
**         -O FILE        True if the file is effectively owned by you.
**         -G FILE        True if the file is effectively owned by your group.
**         -N FILE        True if the file has been modified since it was last
**                        read.
**
**       FILE1 -nt FILE2  True if file1 is newer than file2 (according to
**                        modification date).
**
**       FILE1 -ot FILE2  True if file1 is older than file2.
**
**       FILE1 -ef FILE2  True if file1 is a hard link to file2.
**
**     String operators:
**
**         -z STRING      True if string is empty.
**
**         -n STRING
**         STRING         True if string is not empty.
**
**         STRING1 = STRING2
**                        True if the strings are equal.
**         STRING1 != STRING2
**                        True if the strings are not equal.
**         STRING1 < STRING2
**                        True if STRING1 sorts before STRING2
**                        lexicographically.
**         STRING1 > STRING2
**                        True if STRING1 sorts after STRING2
**                        lexicographically.
**
**     Other operators:
**
**         -o OPTION      True if the shell option OPTION is enabled.
**         ! EXPR         True if expr is false.
**         EXPR1 -a EXPR2 True if both expr1 AND expr2 are true.
**         EXPR1 -o EXPR2 True if either expr1 OR expr2 is true.
**
**         arg1 OP arg2   Arithmetic tests.  OP is one of -eq, -ne,
**                        -lt, -le, -gt, or -ge.
**
**     Arithmetic binary operators return true if ARG1 is equal, not-equal,
**     less-than, less-than-or-equal, greater-than, or greater-than-or-equal
**     than ARG2.
*/

/*
** Grammar taken from the busybox project
** https://git.busybox.net/busybox/tree/coreutils/test.c
**
** """
** test accepts the following grammar:
** 	oexpr   ::= aexpr | aexpr "-o" oexpr ;
** 	aexpr   ::= nexpr | nexpr "-a" aexpr ;
** 	nexpr   ::= primary | "!" primary
** 	primary ::= unary-operator operand
** 		| operand binary-operator operand
** 		| operand
** 		| "(" oexpr ")"
** 		;
** 	unary-operator ::= "-r"|"-w"|"-x"|"-f"|"-d"|"-c"|"-b"|"-p"|
** 		"-u"|"-g"|"-k"|"-s"|"-t"|"-z"|"-n"|"-o"|"-O"|"-G"|"-L"|"-S";
**
** 	binary-operator ::= "="|"=="|"!="|"-eq"|"-ne"|"-ge"|"-gt"|"-le"|"-lt"|
** 			"-nt"|"-ot"|"-ef";
** 	operand ::= <any legal UNIX file name>
** """
*/

typedef enum	e_test_token {
	EOI,

	FILRD,
	FILWR,
	FILEX,

	FILEXIST,

	FILREG,
	FILDIR,
	FILCDEV,
	FILBDEV,
	FILFIFO,
	FILSOCK,

	FILSYM,
	FILGZ,
	FILTT,

	FILSUID,
	FILSGID,
	FILSTCK,

	FILNT,
	FILOT,
	FILEQ,

	FILUID,
	FILGID,

	STREZ,
	STRNZ,
	STREQ,
	STRNE,
	STRLT,
	STRGT,

	INTEQ,
	INTNE,
	INTGE,
	INTGT,
	INTLE,
	INTLT,

	UNOT,
	BAND,
	BOR,
	LPAREN,
	RPAREN,
	OPERAND
}				t_test_token;

typedef enum	e_test_op_type{
	UNOP,
	BINOP,
	BUNOP,
	BBINOP,
	PAREN
}				t_test_op_type;

typedef struct	s_test_op {
	char			*str;
	t_test_token	token;
	t_test_op_type	op_type;
}				t_test_op;

static const t_test_op	g_ops_table[] = {
	{
		.str = "-r",
		.token = FILRD,
		.op_type = UNOP
	},
	{
		.str = "-w",
		.token = FILWR,
		.op_type = UNOP
	},
	{
		.str = "-x",
		.token = FILEX,
		.op_type = UNOP
	},
	{
		.str = "-e",
		.token = FILEXIST,
		.op_type = UNOP
	},
	{
		.str = "-f",
		.token = FILREG,
		.op_type = UNOP
	},
	{
		.str = "-d",
		.token = FILDIR,
		.op_type = UNOP
	},
	{
		.str = "-c",
		.token = FILCDEV,
		.op_type = UNOP
	},
	{
		.str = "-b",
		.token = FILBDEV,
		.op_type = UNOP
	},
	{
		.str = "-p",
		.token = FILFIFO,
		.op_type = UNOP
	},
	{
		.str = "-u",
		.token = FILSUID,
		.op_type = UNOP
	},
	{
		.str = "-g",
		.token = FILSGID,
		.op_type = UNOP
	},
	{
		.str = "-k",
		.token = FILSTCK,
		.op_type = UNOP
	},
	{
		.str = "-s",
		.token = FILGZ,
		.op_type = UNOP
	},
	{
		.str = "-t",
		.token = FILTT,
		.op_type = UNOP
	},
	{
		.str = "-z",
		.token = STREZ,
		.op_type = UNOP
	},
	{
		.str = "-n",
		.token = STRNZ,
		.op_type = UNOP
	},
	{
		.str = "-h",
		.token = FILSYM,
		.op_type = UNOP
	},
	{
		.str = "-O",
		.token = FILUID,
		.op_type = UNOP
	},
	{
		.str = "-G",
		.token = FILGID,
		.op_type = UNOP
	},
	{
		.str = "-L",
		.token = FILSYM,
		.op_type = UNOP
	},
	{
		.str = "-S",
		.token = FILSOCK,
		.op_type = UNOP
	},
	{
		.str = "=",
		.token = STREQ,
		.op_type = BINOP
	},
	{
		.str = "!=",
		.token = STRNE,
		.op_type = BINOP
	},
	{
		.str = "<",
		.token = STRLT,
		.op_type = BINOP
	},
	{
		.str = ">",
		.token = STRGT,
		.op_type = BINOP
	},
	{
		.str = "-eq",
		.token = INTEQ,
		.op_type = BINOP
	},
	{
		.str = "-ne",
		.token = INTNE,
		.op_type = BINOP
	},
	{
		.str = "-ge",
		.token = INTGE,
		.op_type = BINOP
	},
	{
		.str = "-gt",
		.token = INTGT,
		.op_type = BINOP
	},
	{
		.str = "-le",
		.token = INTLE,
		.op_type = BINOP
	},
	{
		.str = "-lt",
		.token = INTLT,
		.op_type = BINOP
	},
	{
		.str = "-nt",
		.token = FILNT,
		.op_type = BINOP
	},
	{
		.str = "-ot",
		.token = FILOT,
		.op_type = BINOP
	},
	{
		.str = "-ef",
		.token = FILEQ,
		.op_type = BINOP
	},
	{
		.str = "!",
		.token = UNOT,
		.op_type = BUNOP
	},
	{
		.str = "-a",
		.token = BAND,
		.op_type = BBINOP
	},
	{
		.str = "-o",
		.token = BOR,
		.op_type = BBINOP
	},
	{
		.str = "(",
		.token = LPAREN,
		.op_type = PAREN
	},
	{
		.str = ")",
		.token = RPAREN,
		.op_type = PAREN
	},
};

#endif
