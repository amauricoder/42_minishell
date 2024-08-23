/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:16:59 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/19 15:29:27 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_user_prompt(char **envp);
static char	*get_pwd_prompt(void);
static char	*clean_prompt(char *str, int flag);
//See function to know how to use it.
//static char	*get_colorful_prompt(char *prompt, int green);

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
	pwd = get_pwd_prompt();
	pwd = clean_prompt(pwd, 1);
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
		free_matriz(str_split);
		return (str);
	}
	free_matriz(str_split);
	return (str);
}

/**
 * @brief Get information from PWD of envp to display at prompt msg.
 * if no PWD envp is available, display a regular msg.
 * @return Char * with information of the PWD.
*/
static char	*get_pwd_prompt(void)
{
	char	cwd[1024];
	char	*directory;

	directory = getcwd(cwd, sizeof(cwd));
	if (!directory)
		return (ft_strdup("Minishell ~"));
	return (ft_strjoin(directory, "-> "));
}
/**
 * @Brief - due to a bug, this function in unused
 * to use it, on function get_prompt_message(), you need to
 * declare "prompt = get_colorful_prompt(prompt, 1);" 
 * after prompt = clean_prompt(prompt, 0);
 * and //pwd = get_colorful_prompt(pwd, 0); after pwd = clean_prompt(pwd, 1);
 */
/* static char	*get_colorful_prompt(char *str, int green)
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
} */
