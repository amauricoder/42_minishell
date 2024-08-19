/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:44 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/19 11:50:44 by aconceic         ###   ########.fr       */
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
		mini_d.stdfds[0] = dup(STDOUT_FILENO); 
		mini_d.stdfds[1] = dup(STDIN_FILENO);
		if (mini_d.prompt != NULL)
			free(mini_d.prompt);
		mini_d.prompt = get_prompt_msg(envp);
		mini_d.input = readline(mini_d.prompt);
		//funcao de verificacao
		if (!mini_d.input)
		{
			printf("exit\n");
			break ;
		}
		else if (check_input(&mini_d, mini_d.input))
		{
			add_history(mini_d.input);
			close(mini_d.stdfds[0]);
			close(mini_d.stdfds[1]);
			continue;
		}
		else if (ft_strlen(mini_d.input) > 0)
		{
			add_history(mini_d.input);
			do_lexing(&mini_d);
			find_expansion(&mini_d);
			define_builtins(&mini_d);
			mini_d.root = build_tree(mini_d.token);
			//tests_builtins(&mini_d, mini_d.root);
			start_execution(&mini_d, mini_d.root);
			debug_nodes_and_tree(&mini_d);
			free_tree(mini_d.root);
			free(mini_d.input);
			free_tokens(&mini_d);
			if (dup2(mini_d.stdfds[0], STDOUT_FILENO) == -1
			|| dup2(mini_d.stdfds[1], STDIN_FILENO) == -1)
			{
				perror("dup2 failed");
				err_msg(&mini_d, "Error redir exec", 1, 0);			
			}
			close(mini_d.stdfds[0]);
			close(mini_d.stdfds[1]);
		}
	}
	free_main_struct(&mini_d);
	return (0);
}
