/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:28:01 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/18 17:49:42 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	execute_cmd(t_mini *mini_d, void *root)
{
	t_exec	*exec_nd;
	char	**path_env;
	char	**envs;
	char	*possible_path;
	int		i;

	exec_nd = root;
	envs = get_env_matriz(mini_d);
	path_env = find_path_env(mini_d);
	if (path_env == NULL)
		return (err_msg(mini_d, ft_strjoin(exec_nd->args[0], NO_DIR), 127, 1));
	if (access(exec_nd->args[0], X_OK) != -1)
		execve(exec_nd->args[0], exec_nd->args, envs);
	i = -1;
	while (path_env[++ i])
	{
		possible_path = create_cmdpath(path_env[i], exec_nd->args[0]);
		if (access(possible_path, X_OK) != -1)
			execve(possible_path, exec_nd->args, envs);
		free(possible_path);
	}
	free_matriz(path_env);
	free_matriz(envs);
	return (err_msg(mini_d, ft_strjoin(exec_nd->args[0], NO_CMD), 127, 1));
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
		if (!ft_strncmp("PATH", env_var->env_name, 4))
			path = ft_strdup(env_var->env_name);
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
		matriz[i] = ft_strdup(nodes->env_name);
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

int	execute_buildins(t_mini *mini, void *root)
{
	t_exec	*exec_node;

	exec_node = (t_exec *)root;  //Function under construction. This comment is here just because norminette will remaind me to correct this shit
	if (exec_node->builtin)
	{
		if (exec_node->builtin == ECHO)
			return (echo(exec_node->args));
		if (exec_node->builtin == PWD)
			return (pwd(mini, exec_node->args));
		if (exec_node->builtin == CD)
			return (cd(mini, exec_node->args));
		if (exec_node->builtin == EXIT)
			exit_read(mini, exec_node->args); // esssa tem que retornar valor
	}
	return (EXIT_FAILURE);
}
