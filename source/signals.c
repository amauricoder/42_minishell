/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:14:59 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/31 19:09:08 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
chamado quando o processo recebe um sinal
exit_status > 128 = processo foi terminado por um sinal
130 - 128 = 2 -> SIGINT (interrupt signal) ctrl+c
 */
void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		printf("\n");
		rl_redisplay();
		g_exit_status = 130;
	}
}

void	signals_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
void	default_sig(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
}
void	update_signals(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);
}

void	heredoc_sig_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_exit_status = 130;
}

void	update_sig_heredoc(void)
{
	struct sigaction sa;

	ft_memset(&sa, 0, sizeof(sa));
    sa.sa_handler = heredoc_sig_handler;
    sigaction(SIGINT, &sa, NULL);
}
/* void	signals_child(void)
{
	struct sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sig, NULL);
	sigaction(SIGINT, &sig, NULL);
} */

/* void	handle_sigpipe(int sig)
{
	(void)sig;
} */

/* void	setup_sigpipe_handler(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigpipe;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGPIPE, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
} */
