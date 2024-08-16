/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:46:33 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/14 17:38:32 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	env_export(t_env *env, t_env **export)
{
	int	size;
	int	i;
	int	j;
	
	size = 0;
	i = 0;
	j = 0;
	while (env->name[size])
		size++;
	size += 13;
	(*export)->name = malloc(sizeof(char) * (size + 1));
	ft_strlcpy((*export)->name, "declare -x ", 11);
	while (env->name[i] != '=')
		i++;
	ft_strlcpy(&(*export)->name[11], env->name, i + 1);
	ft_strlcpy(&(*export)->name[11 + i + 1], "\"", 1);
	while (env->name[i + 1 + j])
		j++;
	ft_strlcpy(&(*export)->name[11 + i + 2], &env->name[i + 1], j);
	ft_strlcpy(&(*export)->name[13 + i + j], "\"", 1);
	(*export)->name[14 + i + j] = '\0';
	if (env->next)
		(*export)->next = malloc(sizeof(t_env));
}

t_env	*export_create(t_mini *mini)
{
	t_env	*export;
	t_env	*env_cpy;
	
	export = malloc(sizeof(t_env));
	export->next = NULL;
	env_cpy = mini->env_d;
	//colocar a env_cpy em ordem alfabetica
	while (env_cpy)
	{
		env_export(env_cpy, &export);
		printf("%s\n", env_cpy->name);
		printf("%s\n", export->name);
		env_cpy = env_cpy->next;
	}
	return (export);
}

int	export_read(t_mini *mini, char **str)
{
	(void)str;
	mini->export = export_create(mini);
	return (0);
}
