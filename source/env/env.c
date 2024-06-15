/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 20:52:47 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/14 20:12:46 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

			//clean properly free_env(env_var)??
int	get_env(char **env, t_env *env_var)
{
	int		i;
	t_env	*new;

	i = 0;
	ft_memset (env_var, 0, sizeof(t_env));
	while (env[i])
	{
		new = ft_calloc(sizeof(t_env), 1);
		if (!new)
			return (EXIT_FAILURE);
		new->env_id = i;
		new->env_name = ft_strdup(env[i]);
		new->next = NULL;
		if (env_var == NULL)
			env_var = new;
		else
			env_var->next = new;
		env_var = new;
		i++;
	}
	return (EXIT_SUCCESS);
}
