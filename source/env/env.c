/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:52:47 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/12 14:33:25 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//clean properly free_env(env_var)??
//getenv()
int	copy_env(char **env, t_env **env_var)
{
	int     i;
	t_env   *new;
	t_env   *last;
	i = 0;
	*env_var = NULL; // Garante que a lista começa vazia.
	while (env[i])
	{
		new = ft_calloc(sizeof(t_env), 1);
		if (!new)
			return (EXIT_FAILURE);
		new->env_id = i;
		new->env_name = ft_strdup(env[i]); // Supondo que env[i] contém o nome da variável de ambiente.
		new->next = NULL;
		if (*env_var == NULL)
			*env_var = new; // Define o primeiro elemento da lista.
		else
			last->next = new; // Adiciona o novo elemento ao final da lista.
		last = new; // Atualiza a referência ao último elemento.
		i++;
	}
	return (EXIT_SUCCESS);
}

int	ft_getenv(t_mini *mini_d, char *to_find)
{
	t_env	*current;

	current = mini_d->env_d;
	while(current)
	{
		if (!ft_strncmp(to_find, current->env_name, ft_strlen(to_find)))
			return (true);
		current = current->next;
	}
	return (false);
}
