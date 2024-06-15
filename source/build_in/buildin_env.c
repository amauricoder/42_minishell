/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:06:41 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/14 20:13:39 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//env with no options or arguments
void	buildin_env(t_env *env_var)
{
	while (env_var->next != NULL)
	{
		ft_putendl_fd(env_var->env_name, 1);
		env_var = env_var->next;
	}
}
