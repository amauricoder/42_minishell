/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:52:47 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/20 19:37:10 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_add(t_mini *mini, char **str)
{
	t_env	*new;
	t_env	*tmp;
	int		i;

	i = 0;
	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	tmp = mini->env_d;
	while (tmp->next)
		tmp = tmp->next;
	while (str[i])
	{
		tmp->name = ft_strjoin(str[i], "=");
		new->name = ft_strjoin(ft_strjoin(str[i], "="), str[i + 1]);
		i += 2;
	}
	tmp->next = new;
	new->next = NULL;
	return ;
}

//clean properly free_env(env_var)??
//getenv()
int	copy_env(char **env, t_env **env_var)
{
	int		i;
	t_env	*new;
	t_env	*last;

	i = 0;
	*env_var = NULL; // Garante que a lista começa vazia.
	while (env[i])
	{
		new = ft_calloc(sizeof(t_env), 1);
		if (!new)
			return (EXIT_FAILURE);
		new->id = i;
		new->name = ft_strdup(env[i]); // Supondo que env[i] contém o nome da variável de ambiente.
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
	while (current)
	{
		if (!ft_strncmp(to_find, current->name, ft_strlen(to_find))
			&& current->name[ft_strlen(to_find)] == '=')
			return (true);
		current = current->next;
	}
	return (false);
}
/**
 * @brief Return a char * of a specific env, or NULL
 */
char	*save_env(t_mini *mini_d, char *to_find)
{
	t_env	*current;
	int		i;

	current = mini_d->env_d;
	while (current)
	{
		if (!ft_strncmp(to_find, current->name, ft_strlen(to_find))
			&& current->name[ft_strlen(to_find)] == '=')
			break;
		current = current->next;
	}
	i = 0;
	if (current->name)
	{
		while (current->name[i] != '=')
			i ++;		
		return (&current->name[i + 1]);
	}
	return (NULL);
}


int	replace_env_value(t_mini *mini, char *env_name, char *new)
{
	t_env	*head;
	char	*tmp;

	head = mini->env_d;
	tmp = ft_strjoin(env_name, "=");
	while(mini->env_d)
	{
		if (!ft_strncmp(mini->env_d->name, env_name, ft_strlen(env_name)))
		{
			free(mini->env_d->name);
			mini->env_d->name = ft_strjoin(tmp, new);
			free(tmp);
			mini->env_d = head;
			return (EXIT_SUCCESS);
		}
		mini->env_d = mini->env_d->next;
	}
	mini->env_d = head;
	free(tmp);
	return (EXIT_SUCCESS);
}
