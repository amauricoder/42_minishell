/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:52:47 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/06 15:09:03 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//returns a single node t_env with the str as the name
t_env	*env_add(char *str)
{
	t_env	*to_add;

	to_add = ft_calloc(sizeof(t_env), 1);
	to_add->name = ft_strdup(str);
	to_add->next = NULL;
	return (to_add);
}

//clean properly free_env(env_var)??
//getenv()
int	copy_env(char **env, t_env **env_var)
{
	int		i;
	t_env	*new;
	t_env	*last;

	i = 0;
	*env_var = NULL;
	while (env[i])
	{
		new = ft_calloc(sizeof(t_env), 1);
		if (!new)
			return (EXIT_FAILURE);
		new->id = i;
		new->name = ft_strdup(env[i]);
		new->next = NULL;
		if (*env_var == NULL)
			*env_var = new;
		else
			last->next = new;
		last = new;
		i++;
	}
	return (EXIT_SUCCESS);
}

//returns tru if finds the "to_find" variable in the env_d linked list
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
char	*expand(t_mini *mini_d, char *to_find)
{
	t_env	*current;
	int		i;

	current = mini_d->env_d;
	while (current)
	{
		if (!ft_strncmp(to_find, current->name, ft_strlen(to_find))
			&& current->name[ft_strlen(to_find)] == '=')
			break ;
		current = current->next;
	}
	i = 0;
	if (!current)
		return (NULL);
	if (current->name)
	{
		while (current->name[i] != '=')
			i ++ ;
		return (&current->name[i + 1]);
	}
	return (NULL);
}

int	replace_env_value(t_mini *mini, char *env_name, char *new)
{
	t_env	*head;
	char	*tmp;

	head = mini->env_d;
	if (!new)
		return (EXIT_FAILURE);
	tmp = ft_strjoin(env_name, "=");
	while (mini->env_d)
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
