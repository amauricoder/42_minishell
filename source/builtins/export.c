/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:46:33 by ismirand          #+#    #+#             */
/*   Updated: 2024/08/16 22:25:14 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export_read(t_mini *mini, char **str)
{
	(void)str;
	mini->export = export_create(mini);
	return (0);
}

t_env	*export_create(t_mini *mini)
{
	t_env	*export;
	t_env	*env_cpy;
	
	export = malloc(sizeof(t_env));
	export->next = NULL;
	env_cpy = lst_sort(mini->env_d);
	while (env_cpy)
	{
		env_export(env_cpy, export);
		//printf("%s\n", env_cpy->name);
		printf("%s\n", export->name);
		env_cpy = env_cpy->next;
	}
	return (export);
}

void	env_export(t_env *env, t_env *export)
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
	if (export->name)//quando faz malloc pra estrutura, ja aloca o primeiro char
		free(export->name);
	export->name = malloc(sizeof(char) * (size + 1));
	ft_strlcpy(export->name, "declare -x ", 12);
	while (env->name[i] != '=')
		i++;
	ft_strlcpy(&export->name[11], env->name, i + 2);
	ft_strlcpy(&export->name[11 + i + 1], "\"", 2);
	while (env->name[i + j])
		j++;
	ft_strlcpy(&export->name[11 + i + 2], &env->name[i + 1], j);
	ft_strlcpy(&export->name[11 + i + j + 1], "\"", 2);
	export->name[13 + i + j] = '\0';
	export->next = NULL;
}

t_env	*lst_sort(t_env *env)
{
    t_env	*tmp;
    t_env	*tmp2;
    char	*swap;

    if (!env)
        return (NULL);
    tmp = env;
    while (tmp)
    {
        tmp2 = tmp->next;
        while (tmp2)
        {
            if (ft_strncmp(tmp->name, tmp2->name, ft_strlen(tmp->name)) > 0)
            {
                swap = tmp->name;
                tmp->name = tmp2->name;
                tmp2->name = swap;
            }
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }
    return (env);
}
