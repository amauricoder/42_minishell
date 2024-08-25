/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:06:41 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/25 17:35:04 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//env with no options or arguments
//se nao tiver nada no env-> msg de erro:
	//minishell: env: No such file or directory
//se exlcuir o path, para de funcionar
void	env(t_env *env_var)
{
	while (env_var != NULL)
	{
		ft_putendl_fd(env_var->name, 1);
		env_var = env_var->next;
	}
}

char	*env_join(char *old, char *to_add, t_env *env)
{
	char	*temp;
	char	*temp2;
	char	*save_name;
	int		i;

	i = 0;
	while (old[i] != '=')
		i++;
	save_name = ft_strdup_qt(old, ++i);
	temp = ft_strtrim(ft_strchr(old, '=') + 1, "\"");
	free (old);
	temp2 = ft_strjoin(save_name, temp);
	free (save_name);
	free (temp);
	env->name = ft_strjoin(temp2, ft_strchr(to_add, '=') + 1);
	free (temp2);
	return (env->name);
}
