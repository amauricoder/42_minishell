/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:52:47 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/29 18:38:45 by aconceic         ###   ########.fr       */
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
            //clean properly
            return (EXIT_FAILURE);
        }
        new->env_id = i;
        new->env_name = ft_strdup(env[i]);
        new->next = NULL;
        if (env_var == NULL)
            env_var = new;
        else
            env_var->next = new;
        env_var = new;
        //printf("%s\n", env_var->env_name);
        i++;
    }
    return (EXIT_SUCCESS);
}
