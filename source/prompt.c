/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:16:59 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/14 21:02:17 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_user_prompt(char **envp);
static char	*get_pwd_prompt(char **envp);
static char	*clean_prompt(char *str, int flag);
//static char	*clean_pwd_prompt(char *pwd);
static char	*get_colorful_prompt(char *prompt, int green);

/**
 * @brief Get information from envp to construct a prompt msg.
 * @return Char * with information for the prompt msg.
 * @attention Wrapper function.
*/
char	*get_prompt_msg(char **envp)
{
	char	*prompt;
	char	*pwd;
	char	*prompt_message;

	prompt = get_user_prompt(envp);
	prompt = clean_prompt(prompt, 0);
	prompt = get_colorful_prompt(prompt, 1);
	pwd = get_pwd_prompt(envp);
	pwd = clean_prompt(pwd, 1);
	pwd = get_colorful_prompt(pwd, 0);
	prompt_message = ft_strjoin(prompt, pwd);
	free(prompt);
	free(pwd);
	return (prompt_message);
}

/**
 * @brief Get information from USER of envp to display at prompt msg.
 * if no USER envp is available, display a regular msg.
 * @return Char * with information of the user.
*/
static	char	*get_user_prompt(char **envp)
{
	int		i;
	int		is_user;
	char	*prompt;

	i = 0;
	is_user = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp("USER", envp[i], 4))
		{
			is_user ++;
			prompt = ft_strjoin(envp[i], "@");
		}
		i ++;
	}
	if (is_user == 0)
		prompt = ft_strdup("Minishell ~");
	return (prompt);
}

/**
 * @brief Take unecessary parts of USER(flag 0) or PWD(flag 1) variable 
 * of envp to display only necessary parts
 * @return Char * with the "clean" information of the USER variable.
*/
static char	*clean_prompt(char *str, int flag)
{
	char	**str_split;
	int		i;

	i = 0;
	str_split = ft_split(str, '=');
	while (str_split[i])
		i ++;
	if (i > 1)
	{
		free(str);
		if (flag == 0)
			str = ft_strjoin(str_split[1], "minishell ~");
		if (flag == 1)
			str = ft_strjoin(str_split[1], "$ " );
		free_dp_char(str_split);
		return (str);
	}
	free_dp_char(str_split);
	return (str);
}

/**
 * @brief Take unecessary parts of PWD variable of envp to display only
 * necessary parts
 * @return Char * with the "clean" information of the PWD variable.
*/
/*
static char	*clean_pwd_prompt(char *pwd)
{
	char	**pwd_split;
	int		i;

	i = 0;
	pwd_split = ft_split(pwd, '=');
	i = 0;
	while (pwd_split[i])
		i ++;
	if (i > 1)
	{
		free(pwd);
		pwd = ft_strjoin(pwd_split[1], "$ ");
		free_dp_char(pwd_split);
		return (pwd);
	}
	free_dp_char(pwd_split);
	return (pwd);
} */

/**
 * @brief Get information from PWD of envp to display at prompt msg.
 * if no PWD envp is available, display a regular msg.
 * @return Char * with information of the PWD.
*/
static char	*get_pwd_prompt(char **envp)
{
	int		i;
	int		is_pwd;
	char	*prompt;

	i = 0;
	is_pwd = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp("PWD", envp[i], 3))
		{
			is_pwd ++;
			prompt = ft_strdup(envp[i]);
		}
		i ++;
	}
	if (is_pwd == 0)
		prompt = ft_strdup("$ ");
	return (prompt);
}

static char	*get_colorful_prompt(char *str, int green)
{
	char	*aux_str1;
	char	*aux_str2;

	if (green)
	{
		aux_str1 = ft_strjoin("\033[32;1m", str);
		aux_str2 = ft_strjoin(aux_str1, "\033[0m");
	}
	else
	{
		aux_str1 = ft_strjoin("\033[34;1m", str);
		aux_str2 = ft_strjoin(aux_str1, "\033[0m");
	}
	free(str);
	free(aux_str1);
	return (aux_str2);
}
