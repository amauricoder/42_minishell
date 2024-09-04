/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:10:43 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/04 19:56:32 by aconceic         ###   ########.fr       */
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
	get_shell(mini_d);
	if (treat_heredocs(mini_d, mini_d->root) == 130
		&& mini_d->qt_heredocs > 0)
	{
		free_run_minishell(mini_d, 1);
		return ;
	}
	do_execution(mini_d, mini_d->root);
	free_run_minishell(mini_d, 0);
}

/**
 * @brief Support function to main()
 * Update the exit_status and the exit_status_printable
 * to always have the right exit_status on the next round
*/
void	update_exit_status(t_mini *mini_d)
{
	if (g_exit_status == 130 || g_exit_status == 131)
		mini_d->exst_printable = g_exit_status;
	mini_d->exit_status = 0;
	g_exit_status = 0;
}

/**
 * @brief Support function to signals(), initialized in run_minishell
 * and called mostly in the signals().
 * Used to save a pointer of the main struct. This way, we can clean
 * after setting and using SIGINT signal.
*/
t_mini	*get_shell(t_mini *new)
{
	static t_mini	*mini = NULL;

	if (new)
		mini = new;
	return (mini);
}
