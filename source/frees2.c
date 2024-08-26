/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:14:36 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/26 17:09:14 by ismirand         ###   ########.fr       */
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
