/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/14 16:44:57 by ismirand         ###   ########.fr       */
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
		if (check_input(&mini_d, mini_d.input))
		{
			printf("VALUE EX %d", mini_d.exit_status);
			add_history(mini_d.input);
			continue;
		}
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

			define_builtins(&mini_d);

			//first, build the tree representation
			mini_d.root = build_tree(mini_d.token); // build the tree

			//TESTES BILLTIN(arvore)
			//then, walk trhgout the tree and execute the commands
			tests_builtins(&mini_d, mini_d.root);
			//andar pela arvore executando os nodes
			//exec_through_tree(&mini_d, mini_d.root);

			//PRINTS FOR DEBUGGING PURPOSES
			printf(ORANGE"-------- MAIN --------\n"RESET);
			printf("\n");
			printf(MGT"-------- PRINT NODES --------\n"RESET);
			printf("\n");
			print_nodes(&mini_d);
			printf("\n");
			printf(MGT"-------- PRINT TREE --------\n"RESET);
			printf("\n");
			print_tree(mini_d.root, "", 0);
			printf("\n");
			printf(ORANGE"-------- END MAIN --------\n"RESET);

			free_tree(mini_d.root);
			free(mini_d.input);
			free_tokens(&mini_d);
			printf("EXIT STATUS %d \n", mini_d.exit_status);
		}
	}
	free_main_struct(&mini_d);
	return (0);
}
