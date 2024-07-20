/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:43:51 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/20 16:06:02 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(t_mini *mini, char **str)
{
	char	cwd[1024];
	char	*dir;	

	if (str[1] && str[2])
		return (error_msg_and_exit(CD_ERR_ARG, EXIT_FAILURE));
	if (!str[1])
	{
		dir = get_path(mini, "HOME");
		//printf("dir if !str[1]-> %s\n", dir);
		if (chdir(dir) == -1)
		{
			printf("dir !str[1] -> %s\n", dir);
			perror("minishell: cd: ");
			free(dir);
			return (EXIT_FAILURE);
		}
		free(dir);
		return (EXIT_SUCCESS);
	}
	if (str[1])
	{
		dir = getcwd(cwd, sizeof(cwd));
		printf("dir str[1] -> %s\n", dir);
		if (!ft_strncmp(str[1], "..", 2))
		{
			dir = find_last_dir(dir);		
			printf("dir find_last_dir -> %s\n", dir);
			if (chdir(dir) == -1)
			{
				perror("minishell: cd: ");
				return (EXIT_FAILURE);
			}
		}
		else if (chdir(str[1]) == -1)
		{
			perror("minishell: cd: ");
			return (EXIT_FAILURE);
		}
	}
	
	return (EXIT_SUCCESS);	
}

char	*find_last_dir(char *dir)
{
	int	i;

	i = ft_strlen(dir);
	while (dir[i] != '/')
		i--;
	dir[i] = '\0';
	return (dir);
}

char	*get_path(t_mini *mini, char *str)
{
	t_env	*current;
	char	**path;
	char	*dir;

	current = mini->env_d;
	dir = NULL;
	while (current)
	{
		if (!ft_strncmp(current->env_name, str, ft_strlen(str)))
		{
			path = ft_split(current->env_name, '=');
			//printf("path -> %s\n", path[1]);
			dir = ft_strdup(path[1]);
			free_matriz(path);
			return (dir);
		}
		current = current->next;
	}
	return (dir);
}
