/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:06:41 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/04 16:32:01 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(t_mini *mini, t_env *env_var, char **str)
{
	if (env_var == NULL)
		return (err_msg(mini, ENV_ERR, 1, 0));
	if (str[1])
		return (err_msg(mini, join_three(D_ENV, str[1], NOF, 0), 127, 1));
	if (!ft_getenv(mini, "PATH"))
		return (err_msg(mini, ft_strjoin(D_ENV, NOF), 127, 1));
	while (env_var != NULL)
	{
		ft_putendl_fd(env_var->name, 1);
		env_var = env_var->next;
	}
	return (EXIT_SUCCESS);
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

//add one more node to the env_d list
void	env_add_one(t_mini *mini, char *name, char *str)
{
	t_env	*env_cpy;

	env_cpy = mini->env_d;
	while (mini->env_d->next)
		mini->env_d = mini->env_d->next;
	mini->env_d->next = ft_calloc(sizeof(t_env), 1);
	mini->env_d = mini->env_d->next;
	mini->env_d->name = ft_strjoin(name, str);
	mini->env_d->next = NULL;
	mini->env_d = env_cpy;
}
