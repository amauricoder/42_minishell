/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:42:59 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/22 18:51:42 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset(t_mini *mini, char **args)
{
	int	i;

	i = 0;
	while (args[++i])
	{
		unset_env(mini, args[i]);
		unset_export(mini, args[i]);
	}
	return (0);
}

void	unset_env(t_mini *mini, char *name)
{
	t_env	*env_cpy;
	t_env	*prev;

	env_cpy = mini->env_d;
	prev = NULL;
	while (mini->env_d)
	{
		if (!ft_strncmp(mini->env_d->name, name, ft_strlen(name))
			&& mini->env_d->name[ft_strlen(name)] == '=')
		{
			if (prev)
				prev->next = mini->env_d->next;
			else
				env_cpy = mini->env_d->next;
			free(mini->env_d->name);
			free(mini->env_d);
			mini->env_d = env_cpy;
			return ;
		}
		prev = mini->env_d;
		mini->env_d = mini->env_d->next;
	}
	mini->env_d = env_cpy;
}

void	unset_export(t_mini *mini, char *name)
{
	t_env	*exp_cpy;
	t_env	*prev;

	exp_cpy = mini->export;
	prev = NULL;
	while (mini->export)
	{
		if (!ft_strncmp(&mini->export->name[11], name, ft_strlen(name))
			&& (mini->export->name[ft_strlen(name) + 11] == '='
			|| mini->export->name[ft_strlen(name) + 11] == '\0'))
		{
			if (prev)
				prev->next = mini->export->next;
			else
				exp_cpy = mini->export->next;
			free(mini->export->name);
			free(mini->export);
			mini->export = exp_cpy;
			return ;
		}
		prev = mini->export;
		mini->export = mini->export->next;
	}
	mini->export = exp_cpy;
}
