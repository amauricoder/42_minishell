/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:43:51 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/20 13:37:52 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(t_mini *mini, char **str)
{
	char	cwd[1024];
	char	*dir;	

	if (str[2])
		return (error_msg_and_exit(CD_ERR_ARG, EXIT_FAILURE));
	if (!str[1])
	{
		dir = get_path(mini, "HOME");
		printf("%s\n", dir);
		//chdir(get_path(mini, "HOME"));
		//return (EXIT_SUCCESS);
	}
	dir = getcwd(cwd, sizeof(cwd));
	(void)mini;
 	if (!dir)
	{
		perror("minishell: cd: "); //treat this properly with exit_status
		return (EXIT_FAILURE);
	}
	printf("%s\n", dir);
	return (EXIT_SUCCESS);	
}

char	*get_path(t_mini *mini, char *str)
{
	t_env	*current;
	char	**path;

	current = mini->env_d;
	while (current)
	{
		if (!ft_strncmp(current->env_name, str, ft_strlen(str)))
		{
			path = ft_split(current->env_name, '=');
			printf("%s\n", path[1]);
			return (path[1]);
		}
		current = current->next;
	}
	return (NULL);
}
