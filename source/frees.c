/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:56:15 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/14 20:17:29 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Clean ** of chars.
 * @attention Called at prompt.c;
*/
void	free_dp_char(char **dp_char)
{
	int	i;

	i = 0;
	while (dp_char[i])
		free(dp_char[i ++]);
	free(dp_char);
}

/**
 * @brief Free main struct itens
*/
int	free_main_struct(t_mini *mini_d)
{
	free(mini_d->input);
	free(mini_d->prompt);
	free_dp_char(mini_d->argv_cp);
	free_env(mini_d->env_d);
	exit(EXIT_SUCCESS);
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
		free(tmp->env_name);
		free(tmp);
	}
	return (0);
}

void	clean_tokens(t_mini *mini_d)
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
