/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/17 09:28:21 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_status = 0;

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini_d;

	if (argc != 1 || !argv)
		return (printf(RED"Try \"./minishell\" instead\n"RESET));
	signals_init();	
	init_main_struct(&mini_d, argv, envp);
	while (1)
	{
		//I need to free the mini_d.input
		mini_d.input = readline(mini_d.prompt);//nao podemos dar free dps?
		if (!mini_d.input)
		{
			printf("exit\n");
			break ;
		}
		if (!ft_strncmp(mini_d.input, "exit", 4) && ft_strlen(mini_d.input) == 4)
		{
			printf("exit");//aqui n tem quebra de linha?
			//here we need to be careful with the free from token struct
			//because of the free at the end. It can enter on  the else too.
			break ;
		}
		else if (ft_strlen(mini_d.input) > 0)
		{
			add_history(mini_d.input);
			//here the magic happens
			//start lexing
			do_lexing(&mini_d);
			//dont forget free all tokens			
			print_nodes(&mini_d);
			free(mini_d.input);
			clean_tokens(&mini_d);
		}
	}
	free_main_struct(&mini_d);
	return (0);
}
