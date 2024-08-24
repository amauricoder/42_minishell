/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:43:51 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/24 11:03:14 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//unset HOME nao esquecer
//eh preciso atualizar o OLD-PWD
//tratar tbm cd ~ (vai pra home)
// tratar cd - cd (volta ao caminho anterior)
//ECHO nao esta printando a $PWD nem $OLDPWD com valor atualizado
//UPDATE
// nao estou tratando special characters

//ATUALIZAR O PWD E O OLDPWD TANTO NO ENV QUANTO NO EXPORT
//fazer funçao join_three
//cd after unsetting HOME -> minishell: cd: HOME not set
//export=zzzz -> retorna prompt, nao adiciona nada --FEITO
int	cd(t_mini *mini, char **str)
{
	printf("nosso cd\n");
	char	*dir;
	char	cwd[1024];

	dir = NULL;
	if ((str[1] && str[2]) || (str[1] && !ft_strncmp(str[1], "...", 3))
		|| (str[1] && !ft_strncmp(str[1], "--", 2)))
		return (err_msg(mini, join_three(D_CD, str[1], NO_FILE, 0), EXIT_FAILURE, 1));
	if (!str[1])
	{
		dir = save_env(mini, "HOME"); // tratar home = NULL
		if (safe_chdir(mini, dir) == -1)
			return (EXIT_FAILURE);
		return (update_pwd_oldpwd(mini, dir));
	}
	else if (!ft_strncmp(&str[1][0], "..", 2))
	{
		dir = getcwd(cwd, sizeof(cwd));
		back_cd(mini, str);
		return (update_pwd_oldpwd(mini, dir));
	}
	else
	{
		dir = ft_strdup(str[1]);
		if (safe_chdir(mini, dir) == -1)
		{
			free(dir);
			return (EXIT_FAILURE);
		}
	}
	if (!dir)
		dir = ft_strdup(save_env(mini, "PWD"));
	update_pwd_oldpwd(mini, dir);
	free(dir);
	return(EXIT_SUCCESS);
}

int	safe_chdir(t_mini *mini, char *dir)
{
	if (chdir(dir) == -1)
	{
		mini->exit_status = err_msg(mini, NULL, EXIT_FAILURE, 0);//acho que ta redundante
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
		if (!ft_strncmp(current->name, str, ft_strlen(str)))
		{
			path = ft_split(current->name, '=');
			printf("path -> %s\n", path[1]);
			dir = ft_strdup(path[1]);
			free_matriz(path);
			return (dir);
		}
		current = current->next;
	}
	return (dir);
}

int	back_cd(t_mini *mini_d, char **str)
{
	int	i;

	i = 0;
	while (str[1][i])
	{
		if (!ft_strncmp(&str[1][i], "..", 2))
		{
			if (safe_chdir(mini_d, "..") == -1)
				return (EXIT_FAILURE);
			i ++;
		}
		i ++;
	}
	return (EXIT_SUCCESS);
}

int	update_pwd_oldpwd(t_mini *mini, char *last_dir)
{
	char	cwd[1024];
	char	*pwd;
	//char	*tmp;

	printf("lastdir %s \n", last_dir);
	pwd = getcwd(cwd, sizeof(cwd));
	printf("PWD %s\n", pwd);
	replace_env_value(mini, "PWD", pwd);
	replace_env_value(mini, "OLDPWD", last_dir);
	return (EXIT_SUCCESS);
}
