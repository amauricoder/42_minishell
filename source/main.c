/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/17 10:42:22 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_tokens(t_mini *mini_d);

int	main(int argc, char **argv, char **envp)
{
	t_mini	mini_d;

	if (!is_argument_valid(argc, envp))
		return (EXIT_FAILURE);	
	init_main_struct(&mini_d, argv, envp);
	while (1)
	{
		mini_d.input = readline(mini_d.prompt);
		//funcao de verificacao
		if (!is_input_valid(mini_d.input))
			break;
		printf("%s\n", mini_d.input);
		if (!mini_d.input || (!ft_strncmp(mini_d.input, "exit", 4)
			&& ft_strlen(mini_d.input) == 4))
		{
			printf("exit\n");
			break ;
		}
		else if (ft_strlen(mini_d.input) > 0)
		{
			add_history(mini_d.input);
			//here the magic happens
			//start lexing
			do_lexing(&mini_d); //dont forget free all tokens		
			print_nodes(&mini_d); // for debug purposes

			free(mini_d.input);
			clean_tokens(&mini_d);
		}
	}
	free_main_struct(&mini_d);
	return (0);
}
