/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:14:59 by ismirand          #+#    #+#             */
/*   Updated: 2024/06/18 10:29:57 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//falta lidar com sinais de processos filhos

/* 
chamado quando o processo recebe um sinal
exit_status > 128 = processo foi terminado por um sinal
130 - 128 = 2 -> SIGINT (interrupt signal) ctrl+c
 */
void	signal_handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);//limpa a linha atual do input
	rl_on_new_line();//pede um novo prompt
	printf("\n");//imprime uma nova linha
	rl_redisplay();//atualiza a exibicao do readline
	g_exit_status = 130;
}

/* 
configura os manipuladores de sinais
 */
void	signals_init(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);//ignora o sinal ctrl+\'
}

void	signal_handler_child(int sig)
{
	if (sig == SIGINT)
		printf("\n");//porque nao fazer igual na signal_handler?
	else
		printf("Quit (core dumped)\n");
}

void	signals_child(void)
{
	signal(SIGINT, signal_handler_child);
	signal(SIGQUIT, signal_handler_child);
}
