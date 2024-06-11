/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:52:47 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/11 16:25:50 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int get_env(char **env, t_env *env_var)
{
    int i;
    t_env *new;
    
    i = 0;

    ft_memset(env_var, 0, sizeof(t_env));
    while (env[i])
    {
        new = malloc(sizeof(t_env));
        if (!new)
        {
            //clean properly free_env(env_var)??
            return (EXIT_FAILURE);
        }
        new->env_id = i;
        new->env_name = ft_strdup(env[i]);
        new->next = NULL;
        if (env_var == NULL)
            env_var = new;
        else
            env_var->next = new;
        env_var = new;//nao entendi
        i++;
    }
    return (EXIT_SUCCESS);
}
