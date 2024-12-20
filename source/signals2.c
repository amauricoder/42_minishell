/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:05:26 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/06 15:35:54 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	update_sig_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = heredoc_sig_handler;
	sigaction(SIGINT, &sa, NULL);
}

void	signals_pipe(void)
{
	signal(SIGPIPE, signal_handler_child);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
