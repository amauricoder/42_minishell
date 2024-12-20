/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:28:01 by aconceic          #+#    #+#             */
/*   Updated: 2024/09/09 16:48:17 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// < inacessible_file | cat -e > output
// erro quando se coloca apenas um redirect e | 
int	execute_cmd(t_mini *mini_d, t_exec *exec_nd)
{
	char	**path_env;
	char	**envs;

	if (!exec_nd->args)
		return (err_msg(mini_d, ft_strjoin("''", NO_CMD), 127, 1));
	path_env = find_path_env(mini_d);
	envs = get_env_matriz(mini_d);
	if (access(exec_nd->args[0], X_OK) != -1)
		execve(exec_nd->args[0], exec_nd->args, envs);
	if (path_env)
		execute_cmd_aux(path_env, envs, exec_nd);
	else
		if (access(exec_nd->args[0], X_OK) != -1)
			execve(exec_nd->args[0], exec_nd->args, envs);
	free_matriz(envs);
	if (path_env == NULL)
		return (err_msg(mini_d, ft_strjoin(exec_nd->args[0], NO_DIR), 127, 1));
	free_matriz(path_env);
	return (err_msg(mini_d, ft_strjoin(exec_nd->args[0], NO_CMD), 127, 1));
}

void	execute_cmd_aux(char **path_env, char **envs, t_exec *exec_nd)
{
	char	*possible_path;
	int		i;

	i = -1;
	while (path_env[++ i])
	{
		possible_path = create_cmdpath(path_env[i], exec_nd->args[0]);
		if (access(possible_path, X_OK) != -1)
			execve(possible_path, exec_nd->args, envs);
		free(possible_path);
	}
}

/**
 * @brief Get path env variable and divide by ':'.
 * @return Return an array from $PATH -> but splitted with ':'.
 */
char	**find_path_env(t_mini	*mini_d)
{
	char	*path;
	char	**path_clean;
	t_env	*env_var;

	env_var = mini_d->env_d;
	path = NULL;
	path_clean = NULL;
	if (!env_var)
		return (NULL);
	while (env_var)
	{
		if (!ft_strncmp("PATH", env_var->name, 4))
			path = ft_strdup(env_var->name);
		env_var = env_var->next;
	}
	if (path != NULL)
	{
		path_clean = ft_split(&path[5], ':');
		free(path);
		return (path_clean);
	}
	return (path_clean);
}

/**
 * @brief Get from the t_env structure, all the nodes names and return a matriz
 * with all the names on it.
 */
char	**get_env_matriz(t_mini *mini_d)
{
	t_env	*nodes;
	char	**matriz;
	int		i;

	i = 0;
	nodes = mini_d->env_d;
	while (nodes)
	{
		i ++;
		nodes = nodes->next;
	}
	matriz = malloc(sizeof(char *) * (i + 1));
	if (!matriz)
		return (NULL);
	i = 0;
	nodes = mini_d->env_d;
	while (nodes)
	{
		matriz[i] = ft_strdup(nodes->name);
		i ++;
		nodes = nodes->next;
	}
	matriz[i] = NULL;
	return (matriz);
}

/**
 * @brief Strjoin possible_path/command.
 * @attention Used on execute_cmd.
 */
char	*create_cmdpath(char *possible_path, char *command)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(possible_path, "/");
	path = ft_strjoin(temp, command);
	free(temp);
	return (path);
}
