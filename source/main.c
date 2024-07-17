/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/17 20:00:00 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_status = 0;

//Problema com $$ -> Retorna o PID. Como fazer???
int	main(int argc, char **argv, char **envp)
{
	t_mini	mini_d;
	
	if (!is_argument_valid(argc, envp))
		return (EXIT_FAILURE);	
	signals_init();	
	init_main_struct(&mini_d, argv, envp);
	while (1)
	{	
		//mini_d.input = readline(mini_d.prompt);
		mini_d.input = readline("Minishell $ ");
		//funcao de verificacao
		if (check_input(mini_d.input))
			add_history(mini_d.input);
		else if (!mini_d.input || (!ft_strncmp(mini_d.input, "exit", 4)
			&& ft_strlen(mini_d.input) == 4))
		{
			printf("exit\n");
			break ;
		}
		else if (ft_strlen(mini_d.input) > 0)
		{
			add_history(mini_d.input);
			do_lexing(&mini_d); //dont forget free all tokens
			find_expansion(&mini_d);

			//execute_buildins(&mini_d); ---> ISA's Function

			//first, build the tree representation
			mini_d.root = build_tree(mini_d.token); // build the tree
			print_tree(mini_d.root, "", 0);
			//then, walk trhgout the tree and execute the commands

			//PRINTS FOR DEBUGGING PURPOSES
			/* 
			printf("\n");
			printf("-------- MAIN --------\n");
			print_nodes(&mini_d);
			 */

			free_tree(mini_d.root);
			free(mini_d.input);
			free_tokens(&mini_d);
		}
	}
	free_main_struct(&mini_d);
	return (0);
}
