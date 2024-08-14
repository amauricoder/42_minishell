/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:28:01 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/14 11:02:08 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// /usr/bin/ls
//which ls
void	execute_cmd(t_mini *mini_d, void *root)
{
	printf("EXECUTE CMD\n");
	t_exec	*exec_nd;
	char	**path_env;
	char	**envs;
	char	*possible_path;
	int		i;

	exec_nd = root;
	envs = get_env_matriz(mini_d);
	path_env = find_path_env(mini_d); // tratar caso path_env seja null
	
	//verificar se eh buildin
		//se for, execute buildin
		//return;

	//verificar se o executavel e encontrado(para caminho completo)
	if (access(exec_nd->args[0], X_OK) != -1) // this is for complete path
	{
		if (execve(exec_nd->args[0], exec_nd->args, envs) == -1)
			printf("erro de exec \n");
	}
	//se chegar aqui, nao caiu na execve
	//preciso verificar pelos possiveis caminhos.
	i = 0;
	while (path_env[i])
	{
		possible_path = create_cmdpath(&possible_path[i], exec_nd->args[0]);
		printf("POSSIBLE_PATH %s \n", possible_path);
		if (access(possible_path, X_OK) != -1)
		{
			if (execve(possible_path, exec_nd->args, envs) == -1)
			printf("erro de exec \n");
		}
		free(possible_path);
		i ++;
	}
	
	//se nao, preciso achar o caminho atraves do Path
	free_matriz(path_env);
	free_matriz(envs);
	(void)mini_d;
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