/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/03 16:10:58 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int g_exit_status = 0;

// Problema com $$ -> Retorna o PID. Como fazer???
// set follow-fork child
// PRECISO
// EXPANSAO HERE_DOC - FEITO
// UNSET -
// VER PROBLEMAS
// tratar LS="ls -l" - FEITO
// tratar export=

// CLEAR ->leaks
// se apagar todos os env, tem que inicializar dnv quando fizer export ou cd
// se fizer qualquer comando, da leak (PORQUE??)

// TRATAR UPDATE DO EXIT_CODE QUANDO APERTA CONTROL + C --- FEITO
// exit ''
//
// echo "' $$$$"' "' << teste safado(mas esta ok)
// exit a a a --> atualizar exit status --> FEITO
// ls | exit --> leak
// ech''o ooo"ss" > '' -- FEITO(imita o comportamento do bash)
// << end - ctrl + c precisa sair do heredoc --- FEITO
// cat | ls -> tratar isso --->
int main(int argc, char **argv, char **envp)
{
	t_mini mini_d;

	if (!is_argument_valid(argc, envp))
		return (EXIT_FAILURE);
	init_main_struct(&mini_d, argv, envp);
	while (1)
	{
		signals_init();
		prompt_and_input(&mini_d);
		if (!mini_d.input)
			break;
		else if (is_input_invalid(&mini_d, mini_d.input))
		{
			add_history(mini_d.input);
			continue;
		}
		else if (ft_strlen(mini_d.input) > 0)
			run_minishell(&mini_d);
		update_exit_status(&mini_d);
	}
	printf("exit\n");
	free_main_struct(&mini_d);
	return (0);
}
