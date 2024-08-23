/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/23 12:17:13 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status = 0;

//Problema com $$ -> Retorna o PID. Como fazer???
//set follow-fork child
//PRECISO
//EXPANSAO HERE_DOC
//UNSET
//VER PROBLEMAS
//consetar funcao de handle signal for the pipe
//tratar LS="ls -l"
//tratar export=
int	main(int argc, char **argv, char **envp)
{
	t_mini	mini_d;

	if (!is_argument_valid(argc, envp))
		return (EXIT_FAILURE);
	signals_init();
	init_main_struct(&mini_d, argv, envp);
	while (1)
	{
		prompt_and_input(&mini_d, envp);
		if (!mini_d.input)
			break ;
		else if (is_input_invalid(&mini_d, mini_d.input))
		{
			add_history(mini_d.input);
			continue ;
		}
		else if (ft_strlen(mini_d.input) > 0)
			run_minishell(&mini_d);
	}
	printf("exit\n");
	free_main_struct(&mini_d);
	return (0);
}

//Preciso
//Here_Doc
//Exit Code
//BuildIns