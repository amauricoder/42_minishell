/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:18:15 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/04 17:12:32 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	treat_exec_exception(t_mini *mini_d, t_exec *exec_node)
{
	int		i;
	int		j;
	int		len;
	char	*equal_pos;

	i = 0;
	j = 0;
	if (is_valid_cmd(mini_d, exec_node->args[i]))
		return(0);
	while (exec_node->args[i])
	{
		if (exec_node->args[i][0] == '=')
			return(0);
		len = ft_strlen(exec_node->args[i]);
		equal_pos = ft_strchr(exec_node->args[i], '=');
		if (equal_pos)
		{
			if (!exec_node->args[i + 1])
				return (1);
			free(exec_node->args[i]);
			j = i;
			move_args_left(exec_node, &j);
		}
		else
			i++;
	}
	return (0);
}

/**
 * @brief Moves the arguments to the left position
 * Ex -> args[3] will become args[2], args[2] will become args[1] and etc..
 * Defines the last argument as NULL
 */
void	move_args_left(t_exec *exec_nd, int *j)
{
	while (exec_nd->args[*j + 1])
	{
		exec_nd->args[*j] = exec_nd->args[*j + 1];
		(*j)++;
	}
	exec_nd->args[*j] = NULL;
}

int	is_valid_cmd(t_mini *mini_d, char *argument)
{
	char	**path_env;
	char	**envs;
	char	*possible_path;
	int		i;
	int		res;

	res = 0;
	path_env = find_path_env(mini_d);
	if (path_env == NULL || !argument)
		res = 0;
	envs = get_env_matriz(mini_d);
	if (access(argument, X_OK) != -1)
		res = 1;
	i = -1;
	while (path_env[++ i])
	{
		possible_path = create_cmdpath(path_env[i], argument);
		if (access(possible_path, X_OK) != -1)
			res = 1;
		free(possible_path);
	}
	free_matriz(path_env);
	free_matriz(envs);
	return (res);
}
