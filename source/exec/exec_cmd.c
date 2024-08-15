/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:28:01 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/15 13:50:37 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// /usr/bin/ls
//which ls
int		execute_cmd(t_mini *mini_d, void *root)
{
	t_exec	*exec_nd;
	char	**path_env;
	char	**envs;
	char	*possible_path;
	int		i;

	exec_nd = root;
	if (exec_nd->builtin != 0)
		return (execute_buildins(mini_d, root));
	envs = get_env_matriz(mini_d);
	path_env = find_path_env(mini_d); // tratar caso path_env seja null
	if (path_env == NULL)
		error_msg(mini_d, CD_ERR_DIR, 130);
	if (access(exec_nd->args[0], X_OK) != -1) // this is for complete path
		execve(exec_nd->args[0], exec_nd->args, envs);
	i = -1;
	while (path_env[++ i]) // This is for possible paths
	{
		possible_path = create_cmdpath(path_env[i], exec_nd->args[0]);
		if (access(possible_path, X_OK) != -1)
			execve(possible_path, exec_nd->args, envs);
		free(possible_path);
	}
	error_msg(mini_d, ERR_CMD_NOT_FOUND, 127);
	free_matriz(path_env);
	free_matriz(envs);
	return(EXIT_FAILURE);
}

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

char	**get_env_matriz(t_mini *mini_d)
{
	t_env	*nodes;
	char	**matriz;
	int		i;

	i = 0;
	nodes = mini_d->env_d;
	while(nodes)
	{
		i ++;
		nodes = nodes->next;
	}
	matriz = malloc(sizeof(char *) * (i + 1));
	if (!matriz)
		return (NULL);
	i = 0;
	nodes = mini_d->env_d;
	while(nodes)
	{
		matriz[i] = ft_strdup(nodes->env_name);
		i ++;
		nodes = nodes->next;
	}
	matriz[i] = NULL;
	return (matriz);
}

char	*create_cmdpath(char *possible_path, char *command)
{
	char	*path;
	char	*temp;

	temp = ft_strjoin(possible_path, "/");
	path = ft_strjoin(temp, command);
	free(temp);
	return (path);
}

//PRECISO QUE ELA RETORNE VALOR
//PRECISO QUE OS BUILDINS RETORNEM VALOR
int	execute_buildins(t_mini *mini, void *root)
{
	t_exec	*exec_node;

	exec_node = (t_exec *)root;
	if (exec_node->builtin)
	{
		if (exec_node->builtin == ECHO)
			return (echo(exec_node->args));
		if (exec_node->builtin == PWD)
			return (pwd(mini, exec_node->args));
		if (exec_node->builtin == CD)
			return (cd(mini, exec_node->args));
		if (exec_node->builtin == EXIT)
			exit_read(mini, exec_node->args);
	}
	return (-1);
}