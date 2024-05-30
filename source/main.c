/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/30 18:35:54 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_mini mini_d;

	init_main_struct(&mini_d, argv, envp);
	while (1)
	{
		mini_d.input = readline(mini_d.prompt);
		if (!mini_d.input)
		{
			printf("exit\n");
			return (0);
		}
		if (!ft_strncmp(mini_d.input, "exit", 4) && ft_strlen(mini_d.input) == 4)
		{
			printf("exit");
			//here we need to be careful with the free from token struct
			//because of the free at the end. It can enter on  the else too.
			break ;
		}
		else
		{
			add_history(mini_d.input);
			//here the magic happens
			//start lexing
			do_lexing(&mini_d);
			//free all tokens
			if (mini_d.token)
				printf("token type -> %i \n", mini_d.token->type);
			free(mini_d.token);
		}
	}
	(void)argc;
	free_main_struct(&mini_d);
	return (0);
}

	//lexer first
	//then parsing


	
	//Lexer -> Expander -> Parser ->Executor
	//(analise lexical - tokenization) - taking user input and proceding
	//char by char into "tokens"

		//start treating user input(how??)
		//1 - lexical analisis(lexing) ----->> doing this
		//2 - syntax analisys (parsing the lexings)