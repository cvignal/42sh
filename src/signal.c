/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvignal <cvignal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:50:27 by cvignal           #+#    #+#             */
/*   Updated: 2019/06/28 08:57:27 by gchainet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>

#include "libft.h"
#include "shell.h"
#include "jobs.h"
#include "fill_line.h"

/*
** How bash react to a given signal versus what a normal prosses do
** 1	SIGHUP		: Kill (Kill)
** 2	SIGINT		: Newline (Kill)		!
** 3	SIGQUIT		: Nothing (Kill)		!
** 4	SIGILL		: Kill (Kill)
** 5	SIGTRAP		: Kill (Kill)
** 6	SIGABRT		: Kill (Kill)
** 7	SIGEMT		: Kill (Kill)
** 8	SIGFPE		: Kill (Kill)
** 9	SIGKILL		: Kill (Kill)
** 10	SIGBUS		: Kill (Kill)
** 11	SIGSEGV		: Kill (Kill)
** 12	SIGSYS		: Kill (Kill)
** 13	SIGPIPE		: Kill (Kill)
** 14	SIGALRM		: Kill (Kill)
** 15	SIGTERM		: Nothing (Kill)		!
** 16	SIGURG		: Nothing (Nothing)
** 17	SIGSTOP		: Kill (Kill)
** 18	SIGTSTP		: Nothing (Kill)		!
** 19	SIGCONT		: Nothing (???)			!
** 20	SIGCHLD		: Nothing (Nothing)
** 21	SIGTTIN		: Nothing (Kill)		!
** 22	SIGTTOU		: Nothing (Kill)		!
** 23	SIGIO		: Nothing (Nothing)
** 24	SIGXCPU		: Kill (Kill)
** 25	SIGXFSZ		: Kill (Kill)
** 26	SIGVTALRM	: Kill (Kill)
** 27	SIGPROF		: Kill (Kill)
** 28	SIGWINCH	: Nothing (Nothing)
** 29	SIGINFO		: Nothing (Nothing)
** 30	SIGUSR1		: Kill (Kill)
** 31	SIGUSR2		: Kill (Kill)
*/

static t_shell	*g_shell = NULL;

void	prompt_signal_handler(int sig)
{
	(void)sig;
	g_shell->ctrlc = 1;
}

void	update_child(int sig)
{
	(void)sig;
	update_jobs(g_shell);
}

void	resize_window(int sig)
{
	(void)sig;
	t_puts("cl");
	print_prompt(g_shell, 0);
	if (g_shell->line.data)
		print_line_bis(g_shell);
	ioctl(0, TIOCGWINSZ, &g_shell->win);
}

void	disable_signal(t_shell *shell)
{
	struct sigaction	sa;

	g_shell = shell;
	ft_bzero(&sa, sizeof(sa));
	sa.sa_handler = prompt_signal_handler;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCHLD, update_child);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGWINCH, resize_window);
}

void	enable_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGWINCH, SIG_DFL);
}
