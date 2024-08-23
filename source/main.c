/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/19 17:15:15 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status = 0;

//Problema com $$ -> Retorna o PID. Como fazer???
//set follow-fork child
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