/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:14:59 by ismirand          #+#    #+#             */
/*   Updated: 2024/09/05 11:31:41 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* 
chamado quando o processo recebe um sinal
exit_status > 128 = processo foi terminado por um sinal
130 - 128 = 2 -> SIGINT (interrupt signal) ctrl+c
 */

void	signals_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

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

void	signals_child(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handler_child(int sig)
{
	t_mini	*shell;

	(void)sig;
	shell = get_shell(NULL);
	free_in_execution(shell, 130);
	exit(130);
}
