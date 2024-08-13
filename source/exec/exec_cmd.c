/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:28:01 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/13 18:37:23 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
// /bin/ls
//which ls
void	execute_cmd(t_mini *mini_d, void *root)
{
	printf("EXECUTE CMD\n");
	t_exec	*exec_nd;
	char	**path_env;
	char	**env;

	exec_nd = root;
	env = get_env_matriz(mini_d);
	path_env = find_path_env(mini_d); // tratar caso path_env seja null
	
	//verificar se eh buildin
		//se for, execute buildin
		//return;

	//primeira coisa, preciso verificar se o executavel esta ali
	//se esta, eviar para execve
	if (access(exec_nd->args[0], X_OK) != -1)
	{
		//execute
		/* printf("entered access execute_cmd\n");
		printf("%s \n", exec_nd->args[0]);
		printf_matriz(exec_nd->args);
		printf_matriz(env); */
		if (execve(exec_nd->args[0], exec_nd->args, env) == -1)
			printf("erro de exec \n");
	}
	
	//se nao, preciso achar o caminho atraves do Path
	free_matriz(path_env);
	free_matriz(env);
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
