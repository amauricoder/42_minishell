/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:14:59 by ismirand          #+#    #+#             */
/*   Updated: 2024/09/03 20:18:41 by aconceic         ###   ########.fr       */
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

void	signal_handler_child(int sig)
{
	t_mini	*shell;

	(void)sig;
	shell = get_shell(NULL);
	free_in_execution(shell, 130);
	exit(130);
}

void	signals_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_child(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_DFL);
}

void	heredoc_sig_handler(int sig)
{
	t_mini	*shell;

	if (sig == SIGINT)
	{
		shell = get_shell(NULL);
		write(1, "\n", 1);
		g_exit_status = 130;
		free_in_execution(shell, 130);
		exit(130);
	}
}

t_mini	*get_shell(t_mini *new)
{
	static t_mini	*mini = NULL;

	if (new)
		mini = new;
	return (mini);
}

void	update_sig_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = heredoc_sig_handler;
	sigaction(SIGINT, &sa, NULL);
}
