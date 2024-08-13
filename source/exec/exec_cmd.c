/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:28:01 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/13 17:27:51 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_cmd(t_mini *mini_d, void *root)
{
	printf("EXECUTE CMD\n");
	t_exec	*exec_nd;
	char	**path_env;

	exec_nd = root;
	path_env = find_path_env(mini_d); // tratar caso path_env seja null
	//primeira coisa, preciso verificar se o executavel esta ali
	//se esta, eviar para execve
	if (access(exec_nd->args[0], F_OK | X_OK))
	{
		//execute 
		execve(exec_nd->args[0], exec_nd->args, path_env);
	}
	
	//se nao, preciso achar o caminho atraves do Path

	free_matriz(path_env);
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
