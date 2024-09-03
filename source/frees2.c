/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:14:36 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/03 15:15:32 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_in_execution(t_mini *mini_d, int exit_status)
{
	if (mini_d->stdfds[0] != -1 && mini_d->stdfds[1] != -1)
	{
		close(mini_d->stdfds[0]);
		close(mini_d->stdfds[1]);
	}
	free_tree(mini_d->root);
	free_tokens(mini_d);
	free(mini_d->input);
	free(mini_d->prompt);
	free_matriz(mini_d->argv_cp);
	free_env(mini_d->env_d);
	free_env(mini_d->export);
	return (exit_status);
}
void	free_run_minishell(t_mini *mini_d, int set_g)
{
	if (set_g)
		g_exit_status = 130;
	free_tree(mini_d->root);
	free(mini_d->input);
	free_tokens(mini_d);
	if (dup2(mini_d->stdfds[0], STDOUT_FILENO) == -1
		|| dup2(mini_d->stdfds[1], STDIN_FILENO) == -1)
		err_msg(mini_d, NULL, 1, 0);
	close(mini_d->stdfds[0]);
	close(mini_d->stdfds[1]);
}