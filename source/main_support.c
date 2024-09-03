/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:10:43 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/03 14:51:58 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Support function to main(), constructed to eat lines
 * construct the prompt and get the user input
 */
void	prompt_and_input(t_mini *mini_d)
{
	char	**minishell_env;

	minishell_env = get_env_matriz(mini_d);
	if (mini_d->prompt != NULL)
		free(mini_d->prompt);
	mini_d->prompt = get_prompt_msg(minishell_env);
	mini_d->input = readline(mini_d->prompt);
	free_matriz(minishell_env);
}

/**
 * @brief Main function of Minishell
 * where the program runs.
 * Do the lexing, parsin, execution of everything.
 * function to debug -> debug_nodes_and_tree(mini_d)
 */
void	run_minishell(t_mini *mini_d)
{
	mini_d->stdfds[0] = dup(STDOUT_FILENO);
	mini_d->stdfds[1] = dup(STDIN_FILENO);
	mini_d->qt_heredocs = 0;
	add_history(mini_d->input);
	do_lexing(mini_d);
	find_expansion(mini_d);
	define_builtins(mini_d);
	mini_d->root = do_parsing(mini_d, mini_d->token);
	//debug_nodes_and_tree(mini_d);
	get_shell(mini_d);
	if (treat_heredocs(mini_d, mini_d->root) == 130
		&& mini_d->qt_heredocs > 0)
	{
		printf("teste\n");
		free_run_minishell(mini_d, 1);
		return ;
	}
	do_execution(mini_d, mini_d->root);
	free_run_minishell(mini_d, 0);
}

//update exit status
void	update_exit_status(t_mini *mini_d)
{
	if (g_exit_status == 130 || g_exit_status == 131)
		mini_d->exst_printable = g_exit_status;
	mini_d->exit_status = 0;
	g_exit_status = 0;
}

