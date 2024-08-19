/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:10:43 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/19 14:16:05 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Main function of Minishell
 * where the program runs.
 * Do the lexing, parsin, execution of everything.
 */
void	run_minishell(t_mini *mini_d)
{
	add_history(mini_d->input);
	do_lexing(mini_d);
	find_expansion(mini_d);
	define_builtins(mini_d);
	mini_d->root = build_tree(mini_d->token);
	start_execution(mini_d, mini_d->root);
	//debug_nodes_and_tree(&mini_d);
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
