/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/29 19:33:32 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env env_var;
	get_env(envp, &env_var);

	
	buildin_env(&env_var);
	(void)argv;
	(void)argc;
	
	char	*input;
	char	*prompt;

	input = NULL;
	prompt = get_prompt_msg(envp);
	while (1)
	{
		input = readline(prompt);
		if (!input)
		{
			printf("exit\n");
			return (0);
		}
		if (!ft_strncmp(input, "exit", 4) && ft_strlen(input) == 4)
		{
			printf("exit");
			break ;
		}
		else
		{
			add_history(input);
			//lexer first
			//then parsing
			parsing1(input, envp);
			//start treating user input(how??)
			//1 - lexical analisis(lexing)
			//2 - syntax analisys (parsing the lexings)
	
			//Lexer -> Expander -> Parser ->Executor

			//(analise lexical - tokenization) - taking user input and proceding
			//char by char into "tokens"
		}
	}
	free(input);
	free(prompt);
	return (0);
}

	/* display the prompt */
    /* read user input */
    /* parser user input into commands and expand variables if have one. */
    /* search the command */
    /* create a child process (fork) */
    /* execute the command(s) (execv)*/
    /* wait for command completion */