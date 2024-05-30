/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/30 14:59:05 by aconceic         ###   ########.fr       */
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
			break ;
		}
		else
		{
			add_history(mini_d.input);
			//here the magic happens
		}
	}
	(void)argc;
	free_main_struct(&mini_d);
	return (0);
}

	/* display the prompt */
    /* read user input */
    /* parser user input into commands and expand variables if have one. */
    /* search the command */
    /* create a child process (fork) */
    /* execute the command(s) (execv)*/
    /* wait for command completion */

	//lexer first
			//then parsing
		
			//start treating user input(how??)
			//1 - lexical analisis(lexing)
			//2 - syntax analisys (parsing the lexings)
	
			//Lexer -> Expander -> Parser ->Executor
			//(analise lexical - tokenization) - taking user input and proceding
			//char by char into "tokens"