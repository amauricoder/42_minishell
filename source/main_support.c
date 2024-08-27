/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:10:43 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/27 19:59:36 by aconceic         ###   ########.fr       */
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
	open_heredocs(mini_d, mini_d->root);
	do_execution(mini_d, mini_d->root);
	free_tree(mini_d->root);
	free(mini_d->input);
	free_tokens(mini_d);
	if (dup2(mini_d->stdfds[0], STDOUT_FILENO) == -1
		|| dup2(mini_d->stdfds[1], STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		err_msg(mini_d, "Error redir exec", 1, 0);
	}
	close(mini_d->stdfds[0]);
	close(mini_d->stdfds[1]);
}
