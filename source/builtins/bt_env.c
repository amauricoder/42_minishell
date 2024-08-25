/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bt_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:06:41 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/25 19:03:52 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//se nao tiver nada no env-> msg de erro: --FEITO
	//minishell: env: No such file or directory
//se tiver algum argumento->msg de erro --FEITO
	//env: "argumento": No such file or directory
//se nao tiver PATH -> "minishell: env: No such file or directory"
//se exlcuir o path, para de funcionar
int	env(t_mini *mini, t_env *env_var, char **str)
{
	if (env_var == NULL)
		return (err_msg(mini, ENV_ERR, 1, 0));
	if (str[1])
		return (err_msg(mini, join_three(D_ENV, str[1], NO_FILE, 0), 1, 1));
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
