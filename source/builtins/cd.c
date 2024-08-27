/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 12:43:51 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/27 19:48:57 by ismirand         ###   ########.fr       */
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
//fazer funçao join_three --FEITO
//cd after unsetting HOME -> minishell: cd: HOME not set --FEITO
//export=zzzz -> retorna prompt, nao adiciona nada --FEITO
//cd -  -> vai pra OLDPWD e printa ele --FEITO
//cd -- vai pra home --FEITO
//cd ~ vai pra home --FEITO
//cd . nao faz nada --FEITO
//tratar se nao tiver OLDPWD --FEITO
int	cd(t_mini *mini, char **str)
{
	char	*dir;
	char	*last_dir;
	char	cwd[1024];

	dir = NULL;
	last_dir = NULL;
	if (str[1] && str[2])
		return (err_msg(mini, ft_strjoin(D_CD, TOO_ARGS), 1, 1));
	if (str[1] && !ft_strncmp(str[1], ".", 1) && !str[1][1])
		return (EXIT_SUCCESS);
	if ((str[1] && !ft_strncmp(str[1], "--", 2) && !str[1][2]) || !str[1]
		|| (!ft_strncmp(str[1], "~", 1) && !str[1][1]))
	{
		dir = expand(mini, "HOME");
		if (!dir && !ft_strncmp(str[1], "~", 1) && !str[1][1])
			dir = getenv("HOME");
		if (!dir)
			return (err_msg(mini, H_NOT, 1, 0));
		last_dir = getcwd(cwd, sizeof(cwd));//ver se tem que dar free
		if (safe_chdir(mini, dir) == -1)
			return (EXIT_FAILURE);
		return (update_pwd_oldpwd(mini, last_dir));
	}
	else if (str[1] && !ft_strncmp(str[1], "..", 2) && !str[1][2])
	{
		dir = getcwd(cwd, sizeof(cwd));
		back_cd(mini, str);
		return (update_pwd_oldpwd(mini, dir));//e se nao tiver algum dos dois?
	}
	else if (str[1] && !ft_strncmp(str[1], "-", 1) && !str[1][1])
	{
		dir = expand(mini, "OLDPWD");//essa troca nao ta certa
		if (!dir)
			return (err_msg(mini, OLDPWD_NOT, 1, 0));
		last_dir = getcwd(cwd, sizeof(cwd));
		printf("%s\n", dir);
		if (safe_chdir(mini, dir) == -1)
			return (EXIT_FAILURE);
		return (update_pwd_oldpwd(mini, last_dir));
	}
	else if (str[1])
	{
		if (safe_chdir(mini, str[1]) == -1)
			return (EXIT_FAILURE);
	}
	//if (!dir)//relembrar se precisa disso ou nao
	//	dir = ft_strdup(expand(mini, "PWD"));//tratar se nao tiver pwd
	update_pwd_oldpwd(mini, dir);
	free(dir);
	return(EXIT_SUCCESS);
}

int	safe_chdir(t_mini *mini, char *dir)
{
	if (chdir(dir) == -1)
	{
		mini->exit_status = err_msg(mini, join_three(D_CD, dir, NO_FILE, 0), 1, 1);
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

//ver o q ela ta fazendo (e igual a safe_env??)
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
	//quando faz cd . -> vai um . pro oldpwd
	//fazer o update deles no export --FEITO
	free_env(mini->export);
	export_create(mini);
	return (EXIT_SUCCESS);
}
