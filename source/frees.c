/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:56:15 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/02 18:15:50 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_and_exit(t_mini *mini, int exit_nbr)
{
	t_exec	*temp;

	temp = mini->root;
	if (mini->token)
	{
		close(mini->stdfds[0]);
		close(mini->stdfds[1]);
		free_tree(mini->root);
		free_tokens(mini);
		free_main_struct(mini);
	}
	printf("caiu no exit\n");
	exit(exit_nbr);
}

/**
 * @brief Free main struct itens
*/
int	free_main_struct(t_mini *mini_d)
{
	close(mini_d->stdfds[0]);
	close(mini_d->stdfds[1]);
	free(mini_d->input);
	free(mini_d->prompt);
	free_matriz(mini_d->argv_cp);
	free_env(mini_d->env_d);
	free_env(mini_d->export);
	return (EXIT_SUCCESS);
}

/**
 * @brief Clean ** of chars.
 * @attention Called at prompt.c;
*/
void	free_matriz(char **dp_char)
{
	int	i;

	i = 0;
	if (!dp_char)
		return ;
	while (dp_char[i])
	{
		free(dp_char[i]);
		i ++;
	}
	free(dp_char);
}

/**
 * @brief Free env nodes
*/
int	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp);
	}
	return (0);
}

/**
 * @brief Free the linked list of tokens and their content
*/
void	free_tokens(t_mini *mini_d)
{
	t_token	*current;
	t_token	*temp;

	current = mini_d->token;
	while (current)
	{
		temp = current;
		current = current->next;
		free(temp->content);
		free(temp);
	}
	mini_d->token = NULL;
}
