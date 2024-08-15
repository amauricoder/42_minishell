/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:43:51 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/15 13:48:00 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(t_mini *mini, char **str)
{
	printf("\n Nossa cd \n");
	char	cwd[1024];
	char	*dir;	

	if (str[1] && str[2])
		return (error_msg(mini, CD_ERR_ARG, EXIT_FAILURE));
	if (!str[1])
	{
		dir = get_path(mini, "HOME");
		printf("cd -> %s\n", dir);//
		if (safe_chdir(mini, dir) == -1)
			return (EXIT_FAILURE);
		free (dir);
	}
	if (str[1])
	{
		dir = getcwd(cwd, sizeof(cwd));
		printf("cd * -> %s/%s\n", dir, str[1]);//
		if (!ft_strncmp(str[1], "..", 2))
		{
			dir = find_last_dir(dir);		
			printf("cd .. -> %s\n", dir);//
			if (safe_chdir(mini, dir) == -1)
				return (EXIT_FAILURE);
		}
		else if (safe_chdir(mini, str[1]) == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);	
}

int	safe_chdir(t_mini *mini, char *dir)
{
	if (chdir(dir) == -1)
	{
		mini->exit_status = error_msg(mini, CD_ERR_DIR, EXIT_FAILURE);//acho que ta redundante
		return (-1);
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
